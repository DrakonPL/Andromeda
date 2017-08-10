#include <Andromeda/Graphics/GXM/VertexArrayObjectGxm.h>
#include <Andromeda/Graphics/RenderManager.h>
#include <psp2/kernel/sysmem.h>
#include "GxmMemoryUtil.h"

namespace Andromeda
{
	namespace Graphics
	{
		VertexArrayObjectGxm::VertexArrayObjectGxm() : VertexArrayObject()
		{
			_gxmPrimitiveType = SCE_GXM_PRIMITIVE_TRIANGLES;
			_gxmIndexFormat = SCE_GXM_INDEX_FORMAT_U16;
		}

		VertexArrayObjectGxm::~VertexArrayObjectGxm()
		{
			GxmMemoryUtil::FreeGpu(_verticesUid);
			GxmMemoryUtil::FreeGpu(_indicesUid);
		}

		void VertexArrayObjectGxm::SetGxmContext(SceGxmContext* gxmContext)
		{
			_gxmContext = gxmContext;
		}

		void VertexArrayObjectGxm::SetVerticesUid(SceUID verticesUid)
		{
			_verticesUid = verticesUid;
		}

		void VertexArrayObjectGxm::SetIndicesUid(SceUID indicesUid)
		{
			_indicesUid = indicesUid;
		}

		void VertexArrayObjectGxm::SetVertexPrimitive(VertexPrimitive vertexPrimitive)
		{
			_vertexPrimitive = vertexPrimitive;

			switch (vertexPrimitive)
			{
			case Triangle:
				_gxmPrimitiveType = SCE_GXM_PRIMITIVE_TRIANGLES;
				break;
			case TriangleFan:
				_gxmPrimitiveType = SCE_GXM_PRIMITIVE_TRIANGLE_FAN;
				break;
			case TriangleStrip:
				_gxmPrimitiveType = SCE_GXM_PRIMITIVE_TRIANGLE_STRIP;
				break;
			case Lines:
				_gxmPrimitiveType = SCE_GXM_PRIMITIVE_LINES;
				break;
			}
		}

		void VertexArrayObjectGxm::SetVertexType(VertexType vertexType)
		{
			_vertexType = vertexType;
			_vertexSize = RenderManager::Instance()->GetVertexSize(vertexType);
		}

		void VertexArrayObjectGxm::SetVertexBufferDrawType(VertexBufferDrawType drawType)
		{
			
		}

		void VertexArrayObjectGxm::CreateVertices(int count)
		{
			_verticesCount = count;

			_vertices = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				_verticesCount * _vertexSize,
				4,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&_verticesUid);
		}

		void VertexArrayObjectGxm::SetVertices(void* data, int count)
		{
			_vertices = data;
			_verticesCount = count;
		}

		void VertexArrayObjectGxm::UpdateVertices(void* data, int count)
		{
			_verticesCount = count;
			std::memcpy(_vertices, data, _verticesCount * _vertexSize);			

			delete[] data;
		}

		void* VertexArrayObjectGxm::GetVertices()
		{
			return _vertices;
		}

		void VertexArrayObjectGxm::CreateIndices(int count)
		{
			_indicesCount = count;

			//create indices
			_indices = GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
				_indicesCount * sizeof(uint16_t),
				2,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&_indicesUid);
		}

		void VertexArrayObjectGxm::SetIndicesNumber(int count)
		{
			_indicesCount = count;
		}

		void VertexArrayObjectGxm::SetIndices(void* data, int count)
		{
			_indices = data;
			_indicesCount = count;
		}

		void VertexArrayObjectGxm::UpdateIndices(void* data, int count)
		{
			_indicesCount = count;
			std::memcpy(_indices, data, _indicesCount * sizeof(uint16_t));			

			delete[] data;
		}

		void* VertexArrayObjectGxm::GetIndices()
		{
			return _indices;
		}

		void VertexArrayObjectGxm::Generate()
		{

		}

		void VertexArrayObjectGxm::Draw()
		{
			if (_vertexPrimitive == Lines)
			{
				sceGxmSetFrontPolygonMode(_gxmContext, SCE_GXM_POLYGON_MODE_LINE);
			}

			sceGxmSetVertexStream(_gxmContext, 0, _vertices);
			sceGxmDraw(_gxmContext, _gxmPrimitiveType, _gxmIndexFormat, _indices, _indicesCount);

			if (_vertexPrimitive == Lines)
			{
				sceGxmSetFrontPolygonMode(_gxmContext, SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);
			}
		}
	}
}

