#include <Andromeda/Graphics/Texture.h>
#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/FileSystem/FileManager.h>

#include <Andromeda/System/MemoryManager.h>

#define  STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Andromeda
{
	namespace Graphics
	{
		Texture::Texture()
		{
			_width = 0;
			_height = 0;
			_textureHeight = 0;
			_textureWidth = 0;
			_id = 0;
			_pixels = 0;
			_filterType = TextureFilerType::LinearFilter;
			_textureColor = TextureColorType::Texture_RGBA;

			_fileName = "";
		}

		Texture::~Texture()
		{
			RenderManager::Instance()->DestroyTexture(this);

			if (_pixels != 0)
			{
				System::MemoryManager::Instance()->FreeTexture(this);
			}
		}

		bool Texture::LoadFromFile(std::string fileName, TextureColorType textureColor, TextureFilerType filterType)
		{
			_fileName = fileName;

			if (_pixels != 0)
			{
				delete[] _pixels;
			}

			FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(_fileName);

			if (file == 0)
				return false;

			file->Open(FileSystem::Read,FileSystem::Binary);

			int dataSize = 0;
			unsigned char* _buffer = file->GetData(dataSize);

			file->Close();
			delete file;

			return LoadFromMemory(fileName, _buffer, dataSize, textureColor, filterType);
		}

		bool Texture::LoadFromMemory(std::string newName, unsigned char* data, std::size_t size, TextureColorType textureColor, TextureFilerType filterType)
		{
			if (data && size)
			{
				_fileName = newName;

				if (_pixels != 0)
				{
					delete[] _pixels;
				}

				// Load the image and get a pointer to the pixels in memory
				int imgWidth, imgHeight, imgChannels;
				const unsigned char* buffer = static_cast<const unsigned char*>(data);
				unsigned char* ptr = stbi_load_from_memory(buffer, static_cast<int>(size), &imgWidth, &imgHeight, &imgChannels, STBI_rgb_alpha);

				if (ptr && imgWidth && imgHeight)
				{
					// Assign the image properties
					_width = imgWidth;
					_height = imgHeight;

					_filterType = filterType;
					_textureColor = textureColor;

					_textureWidth = _width;
					_textureHeight = _height;

					//check if texture size is power of 2
					bool test1 = IsPowerOfTwo(_width);
					bool test2 = IsPowerOfTwo(_height);

					/*if (!test1 || !test2)
					{
						int srcWidth = _width;
						int srcHeigh = _height;

						if (!test1)
						{
							_width = NextPowOf2(_width);
						}

						if (!test2)
						{
							_height = NextPowOf2(_height);
						}

						System::MemoryManager::Instance()->AllocTexture(this);


						int          pitch = srcWidth * 4;
						int          rows = srcHeigh;
						int          srcStride = srcWidth * 4;
						int          dstStride = _width * 4;
						unsigned char*	srcPixels = &ptr[0] + (0 + 0 * srcWidth) * 4;
						unsigned char*  dstPixels = &_pixels[0] + (0 + 0 * _width) * 4;

						// Optimized copy ignoring alpha values, row by row (faster)
						for (int i = 0; i < rows; ++i)
						{
							std::memcpy(dstPixels, srcPixels, pitch);
							srcPixels += srcStride;
							dstPixels += dstStride;
						}
					}
					else*/
					{
						System::MemoryManager::Instance()->AllocTexture(this);

						memcpy(_pixels, ptr, _width * _height * 4);
					}

					// Free the loaded pixels (they are now in our own pixel buffer)
					stbi_image_free(ptr);
					delete[] data;

					return true;
				}
				else
				{
					return false;//error
				}
			}

			return false;
		}

		int Texture::GetWidth()
		{
			return _width;
		}

		int Texture::GetHeight()
		{
			return _height;
		}

		int Texture::GetTextureWidth()
		{
			return _textureWidth;
		}

		int Texture::GetTextureHeight()
		{
			return _textureHeight;
		}

		bool Texture::Resized()
		{
			return _width != _textureWidth || _height != _textureHeight;
		}

		TextureFilerType Texture::GetFilterType()
		{
			return _filterType;
		}

		TextureColorType Texture::GetColorType()
		{
			return _textureColor;
		}

		unsigned int* Texture::GetIdPointer()
		{
			return &_id;
		}

		unsigned int Texture::GetId()
		{
			return _id;
		}

		unsigned char* Texture::GetImageData()
		{
			return _pixels;
		}

		void Texture::SetImageData(void *data)
		{
			_pixels = static_cast<unsigned char*>(data);
		}

		void Texture::CopyImageData(void *data)
		{
			memcpy(_pixels, data, _width * _height * 4);
		}
	}
}

