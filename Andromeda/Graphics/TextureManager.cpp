#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/System/MemoryManager.h>
#include <Andromeda/Utils/Logger.h>

#include <cstdlib>

namespace Andromeda
{
	namespace Graphics
	{
		TextureManager * TextureManager::_textureManager;

		TextureManager::TextureManager()
		{
			
		}

		TextureManager* TextureManager::Instance()
		{
			if (_textureManager == 0)
			{
				_textureManager = new TextureManager();
			}

			return _textureManager;
		}

		Texture* TextureManager::LoadFromFile(std::string fileName, TextureFilerType filterType, TextureColorType textureColor)
		{
			if (_images.find(fileName) == _images.end())
			{
				Texture* image = new Texture();
				if (image->LoadFromFile(fileName, textureColor, filterType))
				{
					//generate texture
					RenderManager::Instance()->CreateTexture(image);

					//add to collection
					_images.insert(std::pair<std::string, Texture*>(fileName, image));

					Utils::Logger_Info("Loaded texture: %s \n", fileName.c_str());

					return image;
				}
				else
				{
					//error
					Utils::Logger_Info("Can't load texture: %s \n", fileName.c_str());
					return 0;
				}
			}

			return _images[fileName];
		}

		Texture* TextureManager::LoadFromMemory(std::string newName, unsigned char *data, std::size_t size, TextureFilerType filterType, TextureColorType textureColor)
		{
			if (_images.find(newName) == _images.end())
			{
				Texture* image = new Texture();
				if (image->LoadFromMemory(newName, data, size, textureColor, filterType))
				{
					//generate texture
					RenderManager::Instance()->CreateTexture(image);

					//add to collection
					_images.insert(std::pair<std::string, Texture*>(newName, image));

					Utils::Logger_Info("Loaded texture: %s \n", newName.c_str());

					return image;
				}
				else
				{
					//error
					Utils::Logger_Info("Can't load texture: %s \n", newName.c_str());
					return 0;
				}
			}

			return _images[newName];
		}

		Texture* TextureManager::CreateEmpty(std::string name, int width, int height, TextureFilerType filterType, TextureColorType textureColor)
		{
			if (name.length() == 0)
			{
				name = GenerateName(16);
			}

			if (_images.find(name) == _images.end())
			{
				Texture* image = new Texture();

				image->_fileName = name;
				image->_width = width;
				image->_height = height;
				image->_textureWidth = width;
				image->_textureHeight = height;
				image->_filterType = filterType;
				image->_textureColor = textureColor;

				//allocate memory to that texture
				System::MemoryManager::Instance()->AllocTexture(image);

				//add to collection
				_images.insert(std::pair<std::string, Texture*>(name, image));

				Utils::Logger_Info("Created texture: %s \n", name.c_str());

				return image;
			}

			return 0;
		}

		Texture* TextureManager::Get(std::string fileName)
		{
			if (_images.find(fileName) == _images.end())
			{
				return 0;
			}

			return _images[fileName];
		}

		void TextureManager::Add(Texture* image)
		{
			if (_images.find(image->_fileName) == _images.end())
			{
				//add to collection
				_images.insert(std::pair<std::string, Texture*>(image->_fileName, image));
			}
		}

		void TextureManager::Remove(std::string fileName)
		{
			std::map<std::string, Texture*>::iterator it = _images.find(fileName);

			if (it == _images.end())
			{
				return;
			}

			delete _images[fileName];
			_images.erase(it);
		}

		void TextureManager::Remove(Texture* image)
		{
			if (image == 0)
			{
				return;
			}

			std::map<std::string, Texture*>::iterator it = _images.find(image->_fileName);

			if (it == _images.end())
			{
				return;
			}

			Utils::Logger_Info("Delete texture: %s \n", it->first.c_str());

			delete image;
			_images.erase(it);
		}

		void TextureManager::RemoveAll()
		{
			std::map<std::string, Texture*>::iterator iter;

			for (iter = _images.begin(); iter != _images.end(); ++iter)
			{
				Utils::Logger_Info("Delete texture: %s \n", iter->first.c_str());

				delete iter->second;
			}

			_images.clear();
		}

		std::string TextureManager::GenerateName(int len)
		{
			std::string generated;
			generated.resize(len);

			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

			for (int i = 0; i < len; ++i)
			{
				generated[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
			}

			generated[len] = 0;

			return generated;
		}
	}
}
