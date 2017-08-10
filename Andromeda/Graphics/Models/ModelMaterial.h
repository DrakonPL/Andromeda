#ifndef ModelMaterial_H
#define ModelMaterial_H

#include <Andromeda/Graphics/Texture.h>
#include <Andromeda/Graphics/GraphicsEnums.h>

#include <glm/glm.hpp>

namespace Andromeda
{
	namespace Graphics
	{
		class ModelMaterial
		{
		private:

			//colors
			glm::vec3 _ambientColor;
			glm::vec3 _diffuseColor;
			glm::vec3 _specularColor;

			//textures
			std::string _diffuseTexture;
			std::string _specularTexture;
			std::string _bumpTexture;

		public:

			ModelMaterial();

			void SetColor(MaterialColorType type, glm::vec3 color);
			void SetTextureName(MaterialTextureType type, std::string fileName);

			glm::vec3 GetColor(MaterialColorType type);
			std::string GetTextureName(MaterialTextureType type);

			std::string Name;
			
			//?
			Texture* Image;
		};
	}
}

#endif 