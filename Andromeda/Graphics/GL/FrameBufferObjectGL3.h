#ifndef FrameBufferObjectGL3_H
#define FrameBufferObjectGL3_H

#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/FrameBufferObject.h>

namespace Andromeda
{
	namespace Graphics
	{
		class FrameBufferObjectGL3 : public FrameBufferObject
		{
		private:

			unsigned int _frameBuffer;
			unsigned int _renderBuffer;

			void PrepareBuffer();

		public:

			FrameBufferObjectGL3(int width,int height);
			~FrameBufferObjectGL3();

			void Bind();
			void UnBind();
		};
	}
}

#endif