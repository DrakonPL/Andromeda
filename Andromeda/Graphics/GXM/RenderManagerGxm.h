#ifndef RenderManagerGxm_H
#define RenderManagerGxm_H

#include <Andromeda/Graphics/RenderManager.h>

#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/types.h>
#include <psp2/kernel/sysmem.h>
#include <Andromeda/Graphics/VertexTypes.h>

namespace Andromeda
{
	namespace Graphics
	{
		#define DISPLAY_WIDTH				960
		#define DISPLAY_HEIGHT				544
		#define DISPLAY_STRIDE_IN_PIXELS	1024
		#define DISPLAY_COLOR_FORMAT		SCE_GXM_COLOR_FORMAT_A8B8G8R8
		#define DISPLAY_PIXEL_FORMAT		SCE_DISPLAY_PIXELFORMAT_A8B8G8R8
		#define DISPLAY_BUFFER_COUNT		3
		#define DISPLAY_MAX_PENDING_SWAPS	2
		#define MSAA_MODE					SCE_GXM_MULTISAMPLE_4X//SCE_GXM_MULTISAMPLE_NONE
		#define DEFAULT_TEMP_POOL_SIZE		(1 * 1024 * 1024)
		

		typedef struct gxm_display_data
		{
			void *address;
		} gxm_display_data;

		class RenderManagerGxm : public RenderManager
		{
			//gxm context
			SceUID vdmRingBufferUid;
			SceUID vertexRingBufferUid;
			SceUID fragmentRingBufferUid;
			SceUID fragmentUsseRingBufferUid;
			SceGxmContextParams contextParams;
			SceGxmContext* _gxmContext;

			//render target
			SceGxmRenderTarget* _renderTarget;

			//display buffer data
			void *displayBufferData[DISPLAY_BUFFER_COUNT];
			SceUID displayBufferUid[DISPLAY_BUFFER_COUNT];
			SceGxmColorSurface displaySurface[DISPLAY_BUFFER_COUNT];
			SceGxmSyncObject *displayBufferSync[DISPLAY_BUFFER_COUNT];

			//depth buffer
			SceUID depthBufferUid;
			SceGxmDepthStencilSurface depthSurface;
			void *depthBufferData;

			//shader patcher
			SceUID patcherBufferUid;
			SceUID patcherVertexUsseUid;
			SceUID patcherFragmentUsseUid;
			SceGxmShaderPatcher* _shaderPatcher;

			//shader mess
			SceGxmShaderPatcherId clearVertexProgramId;
			SceGxmShaderPatcherId clearFragmentProgramId;

			//clear programs
			SceGxmVertexProgram *clearVertexProgram;
			SceGxmFragmentProgram *clearFragmentProgram;
			ClearVertex* clearVertices;
			uint16_t *clearIndices;
			SceUID clearVerticesUid;
			SceUID clearIndicesUid;
			const SceGxmProgramParameter* _clearClearColorParam;

			// Temporary memory pool
			/*void *pool_addr;
			SceUID poolUid;
			unsigned int pool_index = 0;
			unsigned int pool_size = 0;*/

			unsigned int backBufferIndex = 0;
			unsigned int frontBufferIndex = 0;

			float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
			int vblank_wait = 1;


			void InitGxm();
			void CreateGxmContext();
			void CreateRenderTarget();			
			void AllocDisplayBuffer();
			void AllocDepthBuffer();
			void CreateGxmShaderPatcher();
			void InitClearShader();
			void InitClearVertices();

		public:

			RenderManagerGxm();

			void Init();
			void Finish();

			void ClearScreen();

			void StartFrame();
			void EndFrame();

			void SetClearColor(unsigned int color);
			void SwapBuffers();

			void CreateTexture(Texture* image);
			void CreateEmptyTexture(Texture* image);
			void DestroyTexture(Texture* image);
			void UseTexture(Texture* image);
			void UpdateTexture(Texture* image, void *data);

			void* CreateVertices(VertexType vertexType, int size);
			VertexArrayObject* CreateVertexArrayObject(VertexType vertexType, VertexBufferDrawType drawType);

			FrameBufferObject* CreateFrameBufferObject(int width, int height);

			Shader* CreateShader();
			std::string GetVertexShaderName();
			std::string GetFragmnetShaderName();

			void SetDepth(bool state);

			void SaveDisplayBuffer(std::string fileName);
		};
	}
}

#endif
