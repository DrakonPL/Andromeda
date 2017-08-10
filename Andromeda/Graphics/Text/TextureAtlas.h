#ifndef TextureAtlas_H
#define TextureAtlas_H

#include <Andromeda/Graphics/TextureManager.h>

#include <texture-atlas.h>
using namespace ftgl;

namespace Andromeda
{
	namespace Graphics
	{
		class TextureAtlas
		{
		private:

			int _width;
			int _height;

			texture_atlas_t* _atlas;

			Texture* _texture;

			unsigned char ComputeY(int r, int g, int b);
			unsigned char* Convert(unsigned char *data, int img_n, int req_comp, int x, int y);

		public :

			TextureAtlas(int width, int height);
			~TextureAtlas();

			texture_atlas_t* GetAtlas();

			Texture* CreateTexture();
			Texture* GetTexture();
		};
	}
}

#endif
