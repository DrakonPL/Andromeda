#ifndef FrameBufferObjectGL3_H
#define FrameBufferObjectGxm_H

#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/FrameBufferObject.h>

#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/types.h>
#include <psp2/kernel/sysmem.h>

namespace Andromeda
{
	namespace Graphics
	{
		class FrameBufferObjectGxm : public FrameBufferObject
		{
		private:

			SceGxmContext* _gxmContext;

			void* _depthBufferData;
			SceUID _depthBufferUid;			
			
			SceGxmTexture _screenTexture;

			SceGxmColorSurface _colorSurface;
			SceGxmDepthStencilSurface _depthSurface;

			SceGxmRenderTarget *_renderTarget;

			void PrepareBuffer();

		public:

			FrameBufferObjectGxm(int width, int height, SceGxmContext* gxmContext);
			~FrameBufferObjectGxm();

			void Bind();
			void UnBind();
		};
	}
}

#endif