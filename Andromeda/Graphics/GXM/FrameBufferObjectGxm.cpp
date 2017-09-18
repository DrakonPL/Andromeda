#include <Andromeda/Graphics/GXM/FrameBufferObjectGxm.h>
#include <Andromeda/Graphics/GXM/GxmMemoryUtil.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Utils/Logger.h>

#define MAX(a, b)					(((a) > (b)) ? (a) : (b))
#define ALIGN(x, a)					(((x) + ((a) - 1)) & ~((a) - 1))
#define DISPLAY_WIDTH				960
#define DISPLAY_HEIGHT				544
#define OFFSCREEN_COLOR_FORMAT		SCE_GXM_COLOR_FORMAT_A8B8G8R8
#define OFFSCREEN_TEXTURE_FORMAT	SCE_GXM_TEXTURE_FORMAT_A8B8G8R8
#define MSAA_MODE					SCE_GXM_MULTISAMPLE_NONE

namespace Andromeda
{
	namespace Graphics
	{
		FrameBufferObjectGxm::FrameBufferObjectGxm(int width, int height, SceGxmContext* gxmContext)
		{
			_gxmContext = gxmContext;

			_width = width;
			_height = height;

			PrepareBuffer();
		}

		FrameBufferObjectGxm::~FrameBufferObjectGxm()
		{
			sceGxmDestroyRenderTarget(_renderTarget);
			
			TextureManager::Instance()->Remove(_texture);

			GxmMemoryUtil::FreeGpu(_depthBufferUid);
		}

		void FrameBufferObjectGxm::PrepareBuffer()
		{
			//create empty texture
			_texture = TextureManager::Instance()->CreateEmpty("", _width, _height, TextureFilerType::LinearFilter);

			//allocate memory for texture
			void* data = Graphics::GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
				_texture->GetWidth() * _texture->GetHeight() * 4,
				SCE_GXM_TEXTURE_ALIGNMENT,
				SCE_GXM_MEMORY_ATTRIB_RW,
				(SceUID *)_texture->GetIdPointer());

			_texture->SetImageData(data);

			//create texture
			RenderManager::Instance()->CreateTexture(_texture);

			// set up the surface
			sceGxmColorSurfaceInit(
				&_colorSurface,
				OFFSCREEN_COLOR_FORMAT,
				SCE_GXM_COLOR_SURFACE_LINEAR,
				SCE_GXM_COLOR_SURFACE_SCALE_NONE,
				SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT,
				_width,
				_height,
				_width,
				_texture->GetImageData());

			// create the depth/stencil surface
			const uint32_t alignedWidth = ALIGN(_width, SCE_GXM_TILE_SIZEX);
			const uint32_t alignedHeight = ALIGN(_height, SCE_GXM_TILE_SIZEY);

			uint32_t sampleCount = alignedWidth*alignedHeight;
			uint32_t depthStrideInSamples = alignedWidth;

			if (MSAA_MODE == SCE_GXM_MULTISAMPLE_4X)
			{
				// samples increase in X and Y
				sampleCount *= 4;
				depthStrideInSamples *= 2;
			}
			else if (MSAA_MODE == SCE_GXM_MULTISAMPLE_2X)
			{
				// samples increase in Y only
				sampleCount *= 2;
			}

			// allocate the depth buffer
			_depthBufferData = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				4 * sampleCount,
				SCE_GXM_DEPTHSTENCIL_SURFACE_ALIGNMENT,
				SCE_GXM_MEMORY_ATTRIB_RW,
				&_depthBufferUid);

			// create the SceGxmDepthStencilSurface structure
			sceGxmDepthStencilSurfaceInit(
				&_depthSurface,
				SCE_GXM_DEPTH_STENCIL_FORMAT_S8D24,
				SCE_GXM_DEPTH_STENCIL_SURFACE_TILED,
				depthStrideInSamples,
				_depthBufferData,
				NULL);

			// create a render target
			// set up parameters
			SceGxmRenderTargetParams params;
			memset(&params, 0, sizeof(SceGxmRenderTargetParams));
			params.flags = 0;
			params.width = _width;
			params.height = _height;
			params.scenesPerFrame = 1;
			params.multisampleMode = MSAA_MODE;
			params.multisampleLocations = 0;
			params.driverMemBlock = -1;

			sceGxmCreateRenderTarget(&params, &_renderTarget);
		}

		void FrameBufferObjectGxm::Bind()
		{
			// set up a scene, render target, no sync required
			sceGxmBeginScene(
				_gxmContext,
				0,
				_renderTarget,
				NULL,
				NULL,
				NULL,
				&_colorSurface,
				&_depthSurface);
		}

		void FrameBufferObjectGxm::UnBind()
		{
			// stop rendering to the render target
			sceGxmEndScene(_gxmContext, NULL, NULL);
		}
	}
}
