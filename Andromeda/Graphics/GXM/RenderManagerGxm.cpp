#include <Andromeda/Graphics/GXM/RenderManagerGxm.h>
#include <Andromeda/Graphics/GXM/GxmMemoryUtil.h>
#include <Andromeda/Graphics/GXM/FrameBufferObjectGxm.h>
#include <Andromeda/Graphics/GXM/VertexArrayObjectGxm.h>
#include <Andromeda/Graphics/GXM/ShaderGxm.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/Utils/Logger.h>

#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/types.h>
#include <psp2/kernel/sysmem.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG(...) printf(__VA_ARGS__)

//shader mess
/*	The build process for the sample embeds the shader programs directly into the
executable using the symbols below.  This is purely for convenience, it is
equivalent to simply load the binary file into memory and cast the contents
to type SceGxmProgram.
*/

extern const SceGxmProgram clear_v_gxp_start;
extern const SceGxmProgram clear_f_gxp_start;

namespace Andromeda
{
	namespace Graphics
	{
		RenderManagerGxm::RenderManagerGxm() : RenderManager()
		{
			_width = DISPLAY_WIDTH;
			_height = DISPLAY_HEIGHT;
		}

		static void display_callback(const void *callback_data)
		{
			SceDisplayFrameBuf framebuf;
			const gxm_display_data *display_data = (const gxm_display_data *)callback_data;

			memset(&framebuf, 0x00, sizeof(SceDisplayFrameBuf));
			framebuf.size = sizeof(SceDisplayFrameBuf);
			framebuf.base = display_data->address;
			framebuf.pitch = DISPLAY_STRIDE_IN_PIXELS;
			framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
			framebuf.width = DISPLAY_WIDTH;
			framebuf.height = DISPLAY_HEIGHT;
			sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

			//if (vblank_wait)
			{
				sceDisplayWaitVblankStart();
			}
		}

		static void *patcher_host_alloc(void *user_data, unsigned int size)
		{
			return malloc(size);
		}

		static void patcher_host_free(void *user_data, void *mem)
		{
			free(mem);
		}



		void RenderManagerGxm::InitGxm()
		{
			int err;

			UNUSED(err);

			SceGxmInitializeParams initializeParams;
			memset(&initializeParams, 0, sizeof(SceGxmInitializeParams));
			initializeParams.flags = 0;
			initializeParams.displayQueueMaxPendingCount = DISPLAY_MAX_PENDING_SWAPS;
			initializeParams.displayQueueCallback = display_callback;
			initializeParams.displayQueueCallbackDataSize = sizeof(gxm_display_data);
			initializeParams.parameterBufferSize = SCE_GXM_DEFAULT_PARAMETER_BUFFER_SIZE;

			err = sceGxmInitialize(&initializeParams);
			//DEBUG("sceGxmInitialize(): 0x%08X\n", err);
		}

		void RenderManagerGxm::CreateGxmContext()
		{
			int err;
			UNUSED(err);

			Utils::Logger::Instance()->Log("CreateGxmContext::vdmRingBuffer\n");
			void *vdmRingBuffer = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE,
				4,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&vdmRingBufferUid);

			Utils::Logger::Instance()->Log("CreateGxmContext::vertexRingBuffer\n");	
			void *vertexRingBuffer = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE,
				4,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&vertexRingBufferUid);

			Utils::Logger::Instance()->Log("CreateGxmContext::fragmentRingBuffer\n");	
			void *fragmentRingBuffer = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE,
				4,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&fragmentRingBufferUid);

			Utils::Logger::Instance()->Log("CreateGxmContext::fragmentUsseRingBuffer\n");	
			unsigned int fragmentUsseRingBufferOffset;
			void *fragmentUsseRingBuffer = GxmMemoryUtil::AllocFragmentUsse(
				SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE,
				&fragmentUsseRingBufferUid,
				&fragmentUsseRingBufferOffset);

			memset(&contextParams, 0, sizeof(SceGxmContextParams));
			contextParams.hostMem = malloc(SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE);
			contextParams.hostMemSize = SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE;
			contextParams.vdmRingBufferMem = vdmRingBuffer;
			contextParams.vdmRingBufferMemSize = SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE;
			contextParams.vertexRingBufferMem = vertexRingBuffer;
			contextParams.vertexRingBufferMemSize = SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE;
			contextParams.fragmentRingBufferMem = fragmentRingBuffer;
			contextParams.fragmentRingBufferMemSize = SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE;
			contextParams.fragmentUsseRingBufferMem = fragmentUsseRingBuffer;
			contextParams.fragmentUsseRingBufferMemSize = SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE;
			contextParams.fragmentUsseRingBufferOffset = fragmentUsseRingBufferOffset;

			err = sceGxmCreateContext(&contextParams, &_gxmContext);
			//DEBUG("sceGxmCreateContext(): 0x%08X\n", err);
		}

		void RenderManagerGxm::CreateRenderTarget()
		{
			int err;
			UNUSED(err);

			SceGxmRenderTargetParams renderTargetParams;
			memset(&renderTargetParams, 0, sizeof(SceGxmRenderTargetParams));
			renderTargetParams.flags = 0;
			renderTargetParams.width = DISPLAY_WIDTH;
			renderTargetParams.height = DISPLAY_HEIGHT;
			renderTargetParams.scenesPerFrame = 1;
			renderTargetParams.multisampleMode = MSAA_MODE;
			renderTargetParams.multisampleLocations = 0;
			renderTargetParams.driverMemBlock = -1; // Invalid UID

			err = sceGxmCreateRenderTarget(&renderTargetParams, &_renderTarget);
			//DEBUG("sceGxmCreateRenderTarget(): 0x%08X\n", err);
		}

		void RenderManagerGxm::AllocDisplayBuffer()
		{
			int err;
			UNUSED(err);
			unsigned int i, x, y;

			for (i = 0; i < DISPLAY_BUFFER_COUNT; i++)
			{
				// allocate memory for display
				displayBufferData[i] = GxmMemoryUtil::AllocGpu(
					SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
					4 * DISPLAY_STRIDE_IN_PIXELS*DISPLAY_HEIGHT,
					SCE_GXM_COLOR_SURFACE_ALIGNMENT,
					SCE_GXM_MEMORY_ATTRIB_RW,
					&displayBufferUid[i]);

				// memset the buffer to black
				for (y = 0; y < DISPLAY_HEIGHT; y++) 
				{
					unsigned int *row = (unsigned int *)displayBufferData[i] + y*DISPLAY_STRIDE_IN_PIXELS;
					for (x = 0; x < DISPLAY_WIDTH; x++)
					{
						row[x] = 0xff000000;
					}
				}

				// initialize a color surface for this display buffer
				err = sceGxmColorSurfaceInit(
					&displaySurface[i],
					DISPLAY_COLOR_FORMAT,
					SCE_GXM_COLOR_SURFACE_LINEAR,
					(MSAA_MODE == SCE_GXM_MULTISAMPLE_NONE) ? SCE_GXM_COLOR_SURFACE_SCALE_NONE : SCE_GXM_COLOR_SURFACE_SCALE_MSAA_DOWNSCALE,
					SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT,
					DISPLAY_WIDTH,
					DISPLAY_HEIGHT,
					DISPLAY_STRIDE_IN_PIXELS,
					displayBufferData[i]);

				// create a sync object that we will associate with this buffer
				err = sceGxmSyncObjectCreate(&displayBufferSync[i]);
			}
		}

		void RenderManagerGxm::AllocDepthBuffer()
		{
			int err;
			UNUSED(err);

			// compute the memory footprint of the depth buffer
			const unsigned int alignedWidth = ALIGN(DISPLAY_WIDTH, SCE_GXM_TILE_SIZEX);
			const unsigned int alignedHeight = ALIGN(DISPLAY_HEIGHT, SCE_GXM_TILE_SIZEY);

			unsigned int sampleCount = alignedWidth*alignedHeight;
			unsigned int depthStrideInSamples = alignedWidth;

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
			depthBufferData = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				4 * sampleCount,
				SCE_GXM_DEPTHSTENCIL_SURFACE_ALIGNMENT,
				SCE_GXM_MEMORY_ATTRIB_RW,
				&depthBufferUid);

			// create the SceGxmDepthStencilSurface structure
			err = sceGxmDepthStencilSurfaceInit(
				&depthSurface,
				SCE_GXM_DEPTH_STENCIL_FORMAT_S8D24,
				SCE_GXM_DEPTH_STENCIL_SURFACE_TILED,
				depthStrideInSamples,
				depthBufferData,
				NULL);
		}

		void RenderManagerGxm::CreateGxmShaderPatcher()
		{
			int err;
			UNUSED(err);

			const unsigned int patcherBufferSize = 64 * 1024;
			const unsigned int patcherVertexUsseSize = 64 * 1024;
			const unsigned int patcherFragmentUsseSize = 64 * 1024;

			// allocate memory for buffers and USSE code
			void *patcherBuffer = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				patcherBufferSize,
				4,
				SCE_GXM_MEMORY_ATTRIB_RW,
				&patcherBufferUid);

			unsigned int patcherVertexUsseOffset;
			void *patcherVertexUsse = GxmMemoryUtil::AllocVertexUsse(
				patcherVertexUsseSize,
				&patcherVertexUsseUid,
				&patcherVertexUsseOffset);

			unsigned int patcherFragmentUsseOffset;
			void *patcherFragmentUsse = GxmMemoryUtil::AllocFragmentUsse(
				patcherFragmentUsseSize,
				&patcherFragmentUsseUid,
				&patcherFragmentUsseOffset);

			// create a shader patcher
			SceGxmShaderPatcherParams patcherParams;
			memset(&patcherParams, 0, sizeof(SceGxmShaderPatcherParams));
			patcherParams.userData = NULL;
			patcherParams.hostAllocCallback = &patcher_host_alloc;
			patcherParams.hostFreeCallback = &patcher_host_free;
			patcherParams.bufferAllocCallback = NULL;
			patcherParams.bufferFreeCallback = NULL;
			patcherParams.bufferMem = patcherBuffer;
			patcherParams.bufferMemSize = patcherBufferSize;
			patcherParams.vertexUsseAllocCallback = NULL;
			patcherParams.vertexUsseFreeCallback = NULL;
			patcherParams.vertexUsseMem = patcherVertexUsse;
			patcherParams.vertexUsseMemSize = patcherVertexUsseSize;
			patcherParams.vertexUsseOffset = patcherVertexUsseOffset;
			patcherParams.fragmentUsseAllocCallback = NULL;
			patcherParams.fragmentUsseFreeCallback = NULL;
			patcherParams.fragmentUsseMem = patcherFragmentUsse;
			patcherParams.fragmentUsseMemSize = patcherFragmentUsseSize;
			patcherParams.fragmentUsseOffset = patcherFragmentUsseOffset;

			err = sceGxmShaderPatcherCreate(&patcherParams, &_shaderPatcher);
			//DEBUG("sceGxmShaderPatcherCreate(): 0x%08X\n", err);
		}

		void RenderManagerGxm::InitClearShader()
		{
			int err;
			UNUSED(err);

			// check the shaders
			err = sceGxmProgramCheck(&clear_v_gxp_start);
			DEBUG("clear_v sceGxmProgramCheck(): 0x%08X\n", err);
			err = sceGxmProgramCheck(&clear_f_gxp_start);
			DEBUG("clear_f sceGxmProgramCheck(): 0x%08X\n", err);

			// register programs with the patcher
			err = sceGxmShaderPatcherRegisterProgram(_shaderPatcher, &clear_v_gxp_start, &clearVertexProgramId);
			DEBUG("clear_v sceGxmShaderPatcherRegisterProgram(): 0x%08X\n", err);

			err = sceGxmShaderPatcherRegisterProgram(_shaderPatcher, &clear_f_gxp_start, &clearFragmentProgramId);
			DEBUG("clear_f sceGxmShaderPatcherRegisterProgram(): 0x%08X\n", err);
		}

		void RenderManagerGxm::InitClearVertices()
		{
			int err;
			UNUSED(err);

			//another way to get shader when created
			//const SceGxmProgram *clearProgram = sceGxmShaderPatcherGetProgramFromId(clearVertexProgramId);

			//get atribute index
			const SceGxmProgramParameter *paramClearPositionAttribute = sceGxmProgramFindParameterByName(&clear_v_gxp_start, "aPosition");

			//create clear vertex format
			SceGxmVertexAttribute clearVertexAttributes[1];			
			clearVertexAttributes[0].streamIndex = 0;
			clearVertexAttributes[0].offset = 0;
			clearVertexAttributes[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
			clearVertexAttributes[0].componentCount = 2;
			clearVertexAttributes[0].regIndex = sceGxmProgramParameterGetResourceIndex(paramClearPositionAttribute);
			
			SceGxmVertexStream clearVertexStreams[1];
			clearVertexStreams[0].stride = sizeof(ClearVertex);
			clearVertexStreams[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;

			// create clear programs
			err = sceGxmShaderPatcherCreateVertexProgram(
				_shaderPatcher,
				clearVertexProgramId,
				clearVertexAttributes,
				1,
				clearVertexStreams,
				1,
				&clearVertexProgram);

			DEBUG("clear sceGxmShaderPatcherCreateVertexProgram(): 0x%08X\n", err);

			err = sceGxmShaderPatcherCreateFragmentProgram(
				_shaderPatcher,
				clearFragmentProgramId,
				SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,
				MSAA_MODE,
				NULL,
				&clear_v_gxp_start,
				&clearFragmentProgram);

			DEBUG("clear sceGxmShaderPatcherCreateFragmentProgram(): 0x%08X\n", err);

			//create vertices
			clearVertices = (ClearVertex *)GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				3 * sizeof(ClearVertex),
				4,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&clearVerticesUid);

			//create indices
			clearIndices = (uint16_t *)GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				3 * sizeof(uint16_t),
				2,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&clearIndicesUid);

			clearVertices[0].x = -1.0f;
			clearVertices[0].y = -1.0f;
			clearVertices[1].x = 3.0f;
			clearVertices[1].y = -1.0f;
			clearVertices[2].x = -1.0f;
			clearVertices[2].y = 3.0f;

			clearIndices[0] = 0;
			clearIndices[1] = 1;
			clearIndices[2] = 2;

			// find vertex uniforms by name and cache parameter information
			_clearClearColorParam = sceGxmProgramFindParameterByName(&clear_f_gxp_start, "uClearColor");

			// Allocate memory for the memory pool
			/*pool_size = DEFAULT_TEMP_POOL_SIZE;
			pool_addr = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				pool_size,
				sizeof(void *),
				SCE_GXM_MEMORY_ATTRIB_READ,
				&poolUid);*/

			backBufferIndex = 0;
			frontBufferIndex = 0;
		}

		void RenderManagerGxm::Init()
		{
			Utils::Logger::Instance()->Log("Init GXM start\n");

			InitGxm();
			CreateGxmContext();
			CreateRenderTarget();
			AllocDisplayBuffer();
			AllocDepthBuffer();
			CreateGxmShaderPatcher();
			InitClearShader();
			InitClearVertices();

			SetClearColor(RGBA8(51, 76, 76, 255));

			Utils::Logger::Instance()->Log("Init GXM end\n");
		}

		void RenderManagerGxm::Finish()
		{
			Utils::Logger::Instance()->Log("Finish GXM start\n");
			unsigned int i;

			// wait until rendering is done
			sceGxmFinish(_gxmContext);

			// clean up allocations
			sceGxmShaderPatcherReleaseFragmentProgram(_shaderPatcher, clearFragmentProgram);
			sceGxmShaderPatcherReleaseVertexProgram(_shaderPatcher, clearVertexProgram);
			GxmMemoryUtil::FreeGpu(clearIndicesUid);
			GxmMemoryUtil::FreeGpu(clearVerticesUid);

			// wait until display queue is finished before deallocating display buffers
			sceGxmDisplayQueueFinish();

			// clean up display queue
			GxmMemoryUtil::FreeGpu(depthBufferUid);

			for (i = 0; i < DISPLAY_BUFFER_COUNT; i++)
			{
				// clear the buffer then deallocate
				memset(displayBufferData[i], 0, DISPLAY_HEIGHT*DISPLAY_STRIDE_IN_PIXELS * 4);
				GxmMemoryUtil::FreeGpu(displayBufferUid[i]);

				// destroy the sync object
				sceGxmSyncObjectDestroy(displayBufferSync[i]);
			}

			// free the depth buffer
			GxmMemoryUtil::FreeGpu(depthBufferUid);

			// unregister programs and destroy shader patcher
			sceGxmShaderPatcherUnregisterProgram(_shaderPatcher, clearFragmentProgramId);
			sceGxmShaderPatcherUnregisterProgram(_shaderPatcher, clearVertexProgramId);


			sceGxmShaderPatcherDestroy(_shaderPatcher);

			GxmMemoryUtil::FreeFragmentUsse(patcherFragmentUsseUid);
			GxmMemoryUtil::FreeVertexUsse(patcherVertexUsseUid);
			GxmMemoryUtil::FreeGpu(patcherBufferUid);

			// destroy the render target
			sceGxmDestroyRenderTarget(_renderTarget);

			// destroy context
			sceGxmDestroyContext(_gxmContext);
			GxmMemoryUtil::FreeFragmentUsse(fragmentUsseRingBufferUid);
			GxmMemoryUtil::FreeGpu(fragmentRingBufferUid);
			GxmMemoryUtil::FreeGpu(vertexRingBufferUid);
			GxmMemoryUtil::FreeGpu(vdmRingBufferUid);
			free(contextParams.hostMem);

			//GxmMemoryUtil::FreeGpu(poolUid);

			// terminate libgxm
			sceGxmTerminate();
			
			Utils::Logger::Instance()->Log("Finish GXM end\n");
		}

		void RenderManagerGxm::ClearScreen()
		{
			// set clear shaders
			sceGxmSetVertexProgram(_gxmContext, clearVertexProgram);
			sceGxmSetFragmentProgram(_gxmContext, clearFragmentProgram);

			// set the clear color
			void *color_buffer;
			sceGxmReserveFragmentDefaultUniformBuffer(_gxmContext, &color_buffer);
			sceGxmSetUniformDataF(color_buffer, _clearClearColorParam, 0, 4, clearColor);

			// draw the clear triangle
			sceGxmSetVertexStream(_gxmContext, 0, clearVertices);
			sceGxmDraw(_gxmContext, SCE_GXM_PRIMITIVE_TRIANGLES, SCE_GXM_INDEX_FORMAT_U16, clearIndices, 3);
		}

		void RenderManagerGxm::SetClearColor(unsigned int color)
		{
			clearColor[0] = ((color >> 8 * 0) & 0xFF) / 255.0f;
			clearColor[1] = ((color >> 8 * 1) & 0xFF) / 255.0f;
			clearColor[2] = ((color >> 8 * 2) & 0xFF) / 255.0f;
			clearColor[3] = ((color >> 8 * 3) & 0xFF) / 255.0f;
		}


		void RenderManagerGxm::StartFrame()
		{
			//vita2d_start_drawing();
			/* Reset the temporary memory pool */
			//pool_index = 0;

			sceGxmBeginScene(
				_gxmContext,
				0,
				_renderTarget,
				NULL,
				NULL,
				displayBufferSync[backBufferIndex],
				&displaySurface[backBufferIndex],
				&depthSurface);
		}

		void RenderManagerGxm::EndFrame()
		{
			sceGxmEndScene(_gxmContext, NULL, NULL);
		}


		void RenderManagerGxm::SwapBuffers()
		{
			sceGxmPadHeartbeat(&displaySurface[backBufferIndex], displayBufferSync[backBufferIndex]);

			// queue the display swap for this frame
			gxm_display_data displayData;
			displayData.address = displayBufferData[backBufferIndex];
			sceGxmDisplayQueueAddEntry(
				displayBufferSync[frontBufferIndex],	// OLD fb
				displayBufferSync[backBufferIndex],	// NEW fb
				&displayData);

			// update buffer indices
			frontBufferIndex = backBufferIndex;
			backBufferIndex = (backBufferIndex + 1) % DISPLAY_BUFFER_COUNT;
		}

		void RenderManagerGxm::CreateTexture(Texture* image)
		{
			if (image != 0)
			{
				SceGxmTextureFormat textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;

				switch (image->GetColorType())
				{
				case TextureColorType::Texture_RGB:
					textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;
					break;
				case TextureColorType::Texture_RGBA:
					textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;
					break;
				default:
					textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;
					break;
				}

				if(image->GetMipLevel() > 0)
				{
					//generate all mip map levels
					uint32_t *currentLevelData	= (uint32_t *)image->GetImageData();
					uint32_t currentLevelWidth	= image->GetWidth();
					uint32_t currentLevelHeight	= image->GetHeight();
					
					for(int i = 0; i < image->GetMipLevel(); i++)
					{
						// pointer to the next level of mip data
						uint32_t *nextLevelData = currentLevelData + (currentLevelWidth * currentLevelHeight);
						
						// downscale from current level to next level
						int err = sceGxmTransferDownscale(
								SCE_GXM_TRANSFER_FORMAT_U8U8U8U8_ABGR,			// srcFormat
								currentLevelData,								// srcAddress
								0, 0, currentLevelWidth, currentLevelHeight,	// srcX, srcY, srcWidth, srcHeight
								currentLevelWidth * sizeof(uint32_t),			// srcStride
								SCE_GXM_TRANSFER_FORMAT_U8U8U8U8_ABGR,			// destFormat	
								nextLevelData,									// destAddress
								0, 0,											// destX, destY
								(currentLevelWidth / 2) * sizeof(uint32_t),		// destStride
								NULL,											// syncObject
								SCE_GXM_TRANSFER_FRAGMENT_SYNC,					// syncFlags
								NULL);	
								
						// update 	
						currentLevelData	= nextLevelData;
						currentLevelWidth	= currentLevelWidth / 2;
						currentLevelHeight	= currentLevelHeight / 2;
					}
					
					//create texture
					sceGxmTextureInitLinear((SceGxmTexture *)image->_gxmId, image->GetImageData(),SCE_GXM_TEXTURE_FORMAT_A8B8G8R8, image->GetWidth(), image->GetHeight(), image->GetMipLevel());
				}
				else
				{
					//create texture
					sceGxmTextureInitLinear((SceGxmTexture *)image->_gxmId, image->GetImageData(),SCE_GXM_TEXTURE_FORMAT_A8B8G8R8, image->GetWidth(), image->GetHeight(), 1);
				}

				// Set the texture wrapping parameters
				// Set texture wrapping to REPEAT (usually basic wrapping method)
				int wrapType = SCE_GXM_TEXTURE_ADDR_REPEAT;

				switch (image->GetWrapType())
				{
				case TextureWrapType::ClampToBorder:
					wrapType = SCE_GXM_TEXTURE_ADDR_CLAMP_FULL_BORDER;
					break;
				case TextureWrapType::ClampToEdge:
					wrapType = SCE_GXM_TEXTURE_ADDR_CLAMP;
					break;
				case TextureWrapType::Repeat:
					wrapType = SCE_GXM_TEXTURE_ADDR_REPEAT;
					break;
				case TextureWrapType::MirroredRepeat:
					wrapType = SCE_GXM_TEXTURE_ADDR_MIRROR;
					break;

				default:
					wrapType = SCE_GXM_TEXTURE_ADDR_REPEAT;
					break;
				}
				
				sceGxmTextureSetUAddrMode((SceGxmTexture *)image->_gxmId, wrapType);
				sceGxmTextureSetVAddrMode((SceGxmTexture *)image->_gxmId, wrapType);

				// Set texture filtering parameters
				if (image->GetFilterType() == TextureFilerType::LinearFilter)
				{
					sceGxmTextureSetMinFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_ANISO_LINEAR);
					sceGxmTextureSetMagFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_ANISO_LINEAR);
				}
				else
				{
					sceGxmTextureSetMinFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_POINT);
					sceGxmTextureSetMagFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_POINT);
				}				

				//set mip mapping filter
				sceGxmTextureSetMipFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_MIP_FILTER_ENABLED);
			}
		}

		void RenderManagerGxm::CreateEmptyTexture(Texture* image)
		{
			if (image != 0)
			{
				SceGxmTextureFormat textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;

				switch (image->GetColorType())
				{
				case TextureColorType::Texture_RGB:
					textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;
					break;
				case TextureColorType::Texture_RGBA:
					textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;
					break;
				default:
					textureFormat = SCE_GXM_TEXTURE_FORMAT_A8B8G8R8;
					break;
				}
				
				if(image->GetMipLevel() > 0)
				{
					//generate all mip map levels
					uint32_t *currentLevelData	= (uint32_t *)image->GetImageData();
					uint32_t currentLevelWidth	= image->GetWidth();
					uint32_t currentLevelHeight	= image->GetHeight();
					
					for(int i = 0; i < image->GetMipLevel(); i++)
					{
						// pointer to the next level of mip data
						uint32_t *nextLevelData = currentLevelData + (currentLevelWidth * currentLevelHeight);
						
						// downscale from current level to next level
						int err = sceGxmTransferDownscale(
								SCE_GXM_TRANSFER_FORMAT_U8U8U8U8_ABGR,			// srcFormat
								currentLevelData,								// srcAddress
								0, 0, currentLevelWidth, currentLevelHeight,	// srcX, srcY, srcWidth, srcHeight
								currentLevelWidth * sizeof(uint32_t),			// srcStride
								SCE_GXM_TRANSFER_FORMAT_U8U8U8U8_ABGR,			// destFormat	
								nextLevelData,									// destAddress
								0, 0,											// destX, destY
								(currentLevelWidth / 2) * sizeof(uint32_t),		// destStride
								NULL,											// syncObject
								SCE_GXM_TRANSFER_FRAGMENT_SYNC,					// syncFlags
								NULL);	
								
						// update 	
						currentLevelData	= nextLevelData;
						currentLevelWidth	= currentLevelWidth / 2;
						currentLevelHeight	= currentLevelHeight / 2;
					}
					
					//create texture
					sceGxmTextureInitLinear((SceGxmTexture *)image->_gxmId, image->GetImageData(),SCE_GXM_TEXTURE_FORMAT_A8B8G8R8, image->GetWidth(), image->GetHeight(), image->GetMipLevel());
				}
				else
				{
					//create texture
					sceGxmTextureInitLinear((SceGxmTexture *)image->_gxmId, image->GetImageData(),SCE_GXM_TEXTURE_FORMAT_A8B8G8R8, image->GetWidth(), image->GetHeight(), 1);
				}
				
				// Set the texture wrapping parameters
				// Set texture wrapping to REPEAT (usually basic wrapping method)
				int wrapType = SCE_GXM_TEXTURE_ADDR_REPEAT;

				switch (image->GetWrapType())
				{
				case TextureWrapType::ClampToBorder:
					wrapType = SCE_GXM_TEXTURE_ADDR_CLAMP_FULL_BORDER;
					break;
				case TextureWrapType::ClampToEdge:
					wrapType = SCE_GXM_TEXTURE_ADDR_CLAMP;
					break;
				case TextureWrapType::Repeat:
					wrapType = SCE_GXM_TEXTURE_ADDR_REPEAT;
					break;
				case TextureWrapType::MirroredRepeat:
					wrapType = SCE_GXM_TEXTURE_ADDR_MIRROR;
					break;

				default:
					wrapType = SCE_GXM_TEXTURE_ADDR_REPEAT;
					break;
				}
				
				sceGxmTextureSetUAddrMode((SceGxmTexture *)image->_gxmId, wrapType);
				sceGxmTextureSetVAddrMode((SceGxmTexture *)image->_gxmId, wrapType);

				// Set texture filtering parameters
				if (image->GetFilterType() == TextureFilerType::LinearFilter)
				{
					sceGxmTextureSetMinFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_ANISO_LINEAR);
					sceGxmTextureSetMagFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_ANISO_LINEAR);
				}
				else
				{
					sceGxmTextureSetMinFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_POINT);
					sceGxmTextureSetMagFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_FILTER_POINT);
				}				

				//set mip mapping filter
				sceGxmTextureSetMipFilter((SceGxmTexture *)image->_gxmId, SCE_GXM_TEXTURE_MIP_FILTER_ENABLED);
			}
		}

		void RenderManagerGxm::DestroyTexture(Texture* image)
		{
			//??
		}

		void RenderManagerGxm::UseTexture(Texture* image)
		{
			if (image != 0)
			{
				//set texture to TEXUNIT0
				sceGxmSetFragmentTexture(_gxmContext, 0, (SceGxmTexture *)image->_gxmId);
			}
		}

		void RenderManagerGxm::UpdateTexture(Texture* image, void *data)
		{

		}

		void* RenderManagerGxm::CreateVertices(VertexType vertexType, int size)
		{
			return 0;
		}

		VertexArrayObject* RenderManagerGxm::CreateVertexArrayObject(VertexType vertexType, VertexBufferDrawType drawType)
		{
			VertexArrayObjectGxm* _vertexArray = new VertexArrayObjectGxm();

			//set basic info
			_vertexArray->SetGxmContext(_gxmContext);
			_vertexArray->SetVertexType(vertexType);
			_vertexArray->SetVertexPrimitive(Triangle);

			return _vertexArray;
		}

		FrameBufferObject* RenderManagerGxm::CreateFrameBufferObject(int width, int height)
		{
			FrameBufferObjectGxm* fbo = new FrameBufferObjectGxm(width, height, _gxmContext);

			return fbo;
		}

		Shader* RenderManagerGxm::CreateShader()
		{
			ShaderGxm* shader = new ShaderGxm();
			shader->SetShaderPatcher(_shaderPatcher);
			shader->SetGxmContext(_gxmContext);

			return shader;
		}

		std::string RenderManagerGxm::GetVertexShaderName()
		{
			return "_v.gxp";
		}

		std::string RenderManagerGxm::GetFragmnetShaderName()
		{
			return "_f.gxp";
		}

		void RenderManagerGxm::SetDepth(bool state)
		{
			//probablly nothing to do here...
		}

		#define STB_IMAGE_WRITE_IMPLEMENTATION
		#include "stb_image.h"
		#include "stb_image_write.h"

		void RenderManagerGxm::SaveDisplayBuffer(std::string fileName)
		{
			Utils::Logger::Instance()->Log("SaveDisplayBuffer\n");

			//get display buffer
			SceDisplayFrameBuf framebuf;
			memset(&framebuf, 0x00, sizeof(SceDisplayFrameBuf));
			framebuf.size = sizeof(SceDisplayFrameBuf);

			sceDisplayWaitVblankStart();
			int ret = sceDisplayGetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

			if (ret != 0)
			{
				Utils::Logger::Instance()->Log("SaveDisplayBuffer - error: 0x%08X\n",ret);
				return;
			}

			stbi_write_png("ux0:/data/test.png", framebuf.width, framebuf.height, 4, framebuf.base, framebuf.pitch * 4);
		}
	}
}
