#ifndef VertexTypes_H
#define VertexTypes_H

namespace Andromeda
{
	namespace Graphics
	{
		typedef struct
		{
			float x, y;
		}ClearVertex;

		typedef struct
		{
			float x, y, z;
		}SimpleVertex;

		typedef struct
		{
			float x, y, z;
			float r, g, b;
		}ColorVertex;

		typedef struct
		{
			float x, y, z;
			float u, v;
		}TextureVertex;

		typedef struct
		{
			float x, y, z;
			float nx, ny, nz;
			float u, v;
		}TextureNormalVertex;

		typedef struct
		{
			float x, y, z;
			float r, g, b;
			float u, v;
		}TextureColorVertex;

		typedef struct
		{
			float x, y, z;
			float r, g, b, a;
			float nx, ny, nz;
		}ColorNormalVertex;

		typedef struct
		{
			float x, y, z;
			float u, v;
			float r, g, b, a;
			float nx, ny, nz;
		}TextureColorNormalVertex;
	}
}

#endif
