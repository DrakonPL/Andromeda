#ifndef Image_H
#define Image_H

#include <Andromeda/Graphics/GraphicsEnums.h>
#include <string>

namespace Andromeda
{
	namespace Graphics
	{
		class TextureManager;

		class Texture
		{
		private:

			int _width;
			int _height;
			int _textureWidth;
			int _textureHeight;

			TextureFilerType _filterType;
			TextureColorType _textureColor;

			//opengl
			unsigned int _id;			

			std::string _fileName;

			unsigned char *_pixels;

			Texture();


			bool IsPowerOfTwo(unsigned long x)
			{
				return (x & (x - 1)) == 0;
			}

			int NextPowOf2(int dimension)
			{
				int b = dimension;
				int n;
				for (n = 0; b != 0; n++) b >>= 1;
				b = 1 << n;
				if (b == 2 * dimension) b >>= 1;
				return b;
			}

		public:

			~Texture();

			//gxm
			unsigned int _gxmId[4];

			//load image from file
			bool LoadFromFile(std::string fileName, TextureColorType textureColor, TextureFilerType filterType);

			//load image from memory
			bool LoadFromMemory(std::string newName, unsigned char *data, std::size_t size, TextureColorType textureColor, TextureFilerType filterType);

			bool Resized();

			int GetWidth();
			int GetHeight();

			int GetTextureWidth();
			int GetTextureHeight();

			TextureFilerType GetFilterType();
			TextureColorType GetColorType();

			unsigned int* GetIdPointer();
			unsigned int GetId();

			unsigned char* GetImageData();
			void SetImageData(void *data);
			void CopyImageData(void *data);

			friend class TextureManager;

		};
	}
}

#endif
