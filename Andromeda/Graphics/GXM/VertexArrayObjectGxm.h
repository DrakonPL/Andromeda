#ifndef VertexArrayObjectGxm_H
#define VertexArrayObjectGxm_H

#include <Andromeda/Graphics/VertexArrayObject.h>
#include <psp2/gxm.h>

namespace Andromeda
{
	namespace Graphics
	{
		class RenderManagerGxm;

		class VertexArrayObjectGxm : public VertexArrayObject
		{
		protected:

			SceGxmPrimitiveType _gxmPrimitiveType;
			SceGxmIndexFormat _gxmIndexFormat;

			SceUID _verticesUid;
			SceUID _indicesUid;

			SceGxmContext* _gxmContext;			

		public:

			VertexArrayObjectGxm();
			~VertexArrayObjectGxm();

			void SetGxmContext(SceGxmContext* gxmContext);

			void SetVerticesUid(SceUID verticesUid);
			void SetIndicesUid(SceUID indicesUid);

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

			friend class RenderManagerGxm;
		};
	}
}

#endif
