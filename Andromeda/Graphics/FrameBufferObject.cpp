#include <Andromeda/Graphics/FrameBufferObject.h>

namespace Andromeda
{
	namespace Graphics
	{
		FrameBufferObject::~FrameBufferObject()
		{

		}

		Texture* FrameBufferObject::GetTexture()
		{
			return _texture;
		}

		int FrameBufferObject::GetWidth()
		{
			return _width;
		}

		int FrameBufferObject::GetHeight()
		{
			return _height;
		}
	}
}
