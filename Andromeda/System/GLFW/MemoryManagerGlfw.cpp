#include <Andromeda/System/GLFW/MemoryManagerGlfw.h>

namespace Andromeda
{
	namespace System
	{
		void MemoryManagerGlfw::AllocTexture(Graphics::Texture* texture)
		{
			int textureSize = texture->GetColorType() == Graphics::TextureColorType::Texture_RGBA ? 4 : 3;

			unsigned char* data = new unsigned char[texture->GetWidth() * texture->GetHeight() * textureSize];
			texture->SetImageData(data);
		}

		void MemoryManagerGlfw::FreeTexture(Graphics::Texture* texture)
		{
			delete[] texture->GetImageData();
			texture->SetImageData(0);
		}
	}
}


