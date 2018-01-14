#ifndef TextureManager_H
#define TextureManager_H

#include <Andromeda/Graphics/Texture.h>
#include <map>

namespace Andromeda
{
	namespace Graphics
	{
		class TextureManager
		{
		private:

			static TextureManager* _textureManager;
			std::map<std::string, Texture*> _images;

			TextureManager();

			std::string GenerateName(int len);

		public:

			static TextureManager* Instance();

			Texture* LoadFromFile(std::string fileName, TextureFilerType filterType = TextureFilerType::LinearFilter, TextureColorType textureColor = TextureColorType::Texture_RGBA, TextureWrapType textureWrap = TextureWrapType::ClampToEdge, int mipLevel = 0);
			Texture* LoadFromMemory(std::string newName, unsigned char *data, size_t size, TextureFilerType filterType = TextureFilerType::LinearFilter, TextureColorType textureColor = TextureColorType::Texture_RGBA, TextureWrapType textureWrap = TextureWrapType::ClampToEdge, int mipLevel = 0);
			
			Texture* CreateEmpty(std::string name, int width, int height, TextureFilerType filterType, TextureColorType textureColor = TextureColorType::Texture_RGBA, TextureWrapType textureWrap = TextureWrapType::ClampToEdge, int mipLevel = 0);

			Texture* Get(std::string fileName);

			void Add(Texture* image);

			void Remove(std::string fileName);
			void Remove(Texture* image);
			void RemoveAll();

		};
	}
}

#endif
