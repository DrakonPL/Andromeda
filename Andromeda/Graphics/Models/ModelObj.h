#ifndef ModelObj_H
#define ModelObj_H

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/Graphics/TextureManager.h>

#include <Andromeda/Graphics/Models/ModelMesh.h>
#include <Andromeda/Graphics/Models/ModelMaterial.h>

#include <vector>

#include <tiny_obj_loader.h>

namespace Andromeda
{
	namespace Graphics
	{
		class ModelObj
		{
		private:

			//meshes
			std::vector<ModelMesh*> _meshes;

			//textures
			std::vector<ModelMaterial*> _materials;

			// Shader
			Shader* _shader;

			//model root directory
			std::string _location;

			//
			glm::vec4 _color;

			//transformation
			glm::mat4 _modelMatrix;

			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;
			
			std::string GetFolderFromPath(std::string& fileName);
			std::string GetFileFromPath(std::string& fileName);

			void LoadModel(std::vector<tinyobj::shape_t> &shapes, std::vector<tinyobj::material_t> &materials, std::string fileName);

		public:

			ModelObj();
			~ModelObj();

			//load standard .obj model
			bool LoadModel(std::string fileName);			

			//load binary model .bobj
			void LoadBinary(std::string fileName);
			
			//convert standard model to binary format
			void ConvertToBinary(std::string fileName,std::string saveFile);

			//shader
			void SetShader(Shader* shader);
			
			Shader* GetShader();

			//transformations
			void SetPosition(glm::vec3 position);
			void SetRotationn(glm::vec3 rotation);
			void SetScale(glm::vec3 scale);
			
			glm::vec3 GetPosition();
			glm::vec3 GetRotation();
			glm::vec3 GetScale();

			glm::mat4 GetModelMatrix();

			//
			void SetColor(glm::vec4 color);
			glm::vec4 GetColor();

			//drawing
			void Draw();
		};
	}
}

#endif 