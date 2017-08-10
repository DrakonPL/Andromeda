#ifndef FrameBufferObject_H
#define FrameBufferObject_H

#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/Texture.h>

namespace Andromeda
{
	namespace Graphics
	{
		class RenderManager;

		class FrameBufferObject
		{
		protected:

			Texture* _texture;

			int _width;
			int _height;

		public:

			virtual ~FrameBufferObject();

			virtual void Bind() = 0;
			virtual void UnBind() = 0;

			Texture* GetTexture();

			int GetWidth();
			int GetHeight();
		};
	}
}

#endif