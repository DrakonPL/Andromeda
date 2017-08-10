#include <Andromeda/Graphics/VertexArrayObject.h>

namespace Andromeda
{
	namespace Graphics
	{
		int VertexArrayObject::_objectCount = 0;

		VertexArrayObject::VertexArrayObject()
		{
			_objectCount++;

			_vertexSize = 0;
			_verticesCount = 0;
			_indicesCount = 0;
		}

		VertexArrayObject::~VertexArrayObject()
		{
			_objectCount--;
		}
	}
}
