#ifndef VertexArrayObjectGL3_H
#define VertexArrayObjectGL3_H

#include <Andromeda/Graphics/VertexArrayObject.h>

#define BUFFER_OFFSET(i) ((void*)(i))

namespace Andromeda
{
	namespace Graphics
	{
		class VertexArrayObjectGL3 : public VertexArrayObject
		{

		protected:

			//vertex array buffer
			unsigned int _vao;

			//vertex buffer object
			unsigned int _vbo;

			//vertex indices buffer
			unsigned int _vbi;

			//draw prymitive
			unsigned int _drawMode;

			void SetVertexArtibutes();

		public :

			VertexArrayObjectGL3();
			~VertexArrayObjectGL3();

			void SetVertexPrimitive(VertexPrimitive vertexPrimitive);
			void SetVertexType(VertexType vertexType);
			void SetVertexBufferDrawType(VertexBufferDrawType drawType);

			void CreateVertices(int count);
			void SetVertices(void* data, int count);
			void UpdateVertices(void* data, int count);
			void* GetVertices();

			void CreateIndices(int count);
			void SetIndicesNumber(int count);
			void SetIndices(void* data, int count);
			void UpdateIndices(void* data, int count);
			void* GetIndices();

			void Generate();

			void Draw();

		};
	}
}

#endif
