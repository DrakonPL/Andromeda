#ifndef ModelMesh_H
#define ModelMesh_H

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/Graphics/TextureManager.h>

namespace Andromeda
{
	namespace Graphics
	{
		class ModelMesh
		{
		public:

			VertexType VertexTyp;

			std::string Name;

			VertexArrayObject* Mesh;

			int MaterialId;

		};
	}
}

#endif 