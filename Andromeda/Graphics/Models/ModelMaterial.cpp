#include "Andromeda/Graphics/Models/ModelMaterial.h"

namespace Andromeda
{
	namespace Graphics
	{
		ModelMaterial::ModelMaterial()
		{
			_ambientColor = glm::vec3(0.0f, 0.0f, 0.0f);
			_diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
			_specularColor = glm::vec3(0.0f, 0.0f, 0.0f);

			//textures
			_diffuseTexture = "";
			_specularTexture = "";
			_bumpTexture = "";

			Image = 0;
		}

		void ModelMaterial::SetColor(MaterialColorType type, glm::vec3 color)
		{
			switch (type)
			{
			case Andromeda::Graphics::MaterialColorAmbient:
				_ambientColor = color;
				break;
			case Andromeda::Graphics::MaterialColorDiffuse:
				_diffuseColor = color;
				break;
			case Andromeda::Graphics::MaterialColorSpecular:
				_specularColor = color;
				break;
			}
		}

		void ModelMaterial::SetTextureName(MaterialTextureType type, std::string fileName)
		{
			switch (type)
			{
			case Andromeda::Graphics::MaterialTextureDiffuse:
				_diffuseTexture = fileName;
				break;
			case Andromeda::Graphics::MaterialTextureSpecular:
				_specularTexture = fileName;
				break;
			case Andromeda::Graphics::MaterialTextureBump:
				_bumpTexture = fileName;
				break;
			}
		}

		glm::vec3 ModelMaterial::GetColor(MaterialColorType type)
		{
			switch (type)
			{
			case Andromeda::Graphics::MaterialColorAmbient:
				return _ambientColor;
				break;
			case Andromeda::Graphics::MaterialColorDiffuse:
				return _diffuseColor;
				break;
			case Andromeda::Graphics::MaterialColorSpecular:
				return _specularColor;
				break;
			}
		}

		std::string ModelMaterial::GetTextureName(MaterialTextureType type)
		{
			switch (type)
			{
			case Andromeda::Graphics::MaterialTextureDiffuse:
				return _diffuseTexture;
				break;
			case Andromeda::Graphics::MaterialTextureSpecular:
				return _specularTexture;
				break;
			case Andromeda::Graphics::MaterialTextureBump:
				return _bumpTexture;
				break;
			}
		}
	}
}