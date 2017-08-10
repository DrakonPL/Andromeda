#ifndef Sprite_H
#define Sprite_H

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/VertexTypes.h>

#include <glm/glm.hpp>

namespace Andromeda
{
	namespace Graphics
	{
		class Sprite
		{
		private:

			static int _objectCount;

			//vertex array
			VertexArrayObject* _arrayObject;

			//shader
			Shader* _shader;

			//texture
			Texture* _texture;

			std::string _name;

			float _angle;
			glm::vec2 _position;
			glm::vec2 _size;
			glm::vec2 _scale;
			glm::vec4 _color;
			glm::vec2 _location;
			
		private:

			void CreateVertexObject(bool customUV);
			void UpdateSize();

		public:

			static int GetObjectCount() { return _objectCount; }

		public:

			Sprite(std::string name, std::string imageName, std::string vertexShader, std::string fragmentShader);
			Sprite(std::string name, std::string imageName, Shader* shader);
			Sprite(std::string name, Texture* texture, Shader* shader);
			Sprite(std::string name, Texture* texture, Shader* shader,glm::vec2 location, glm::vec2 size);

			~Sprite();

			void SetShader(Shader* shader);
			void SetTexture(Texture* texture);

			void SetAngle(float angle);
			void SetPosition(glm::vec2 position);
			void SetSize(glm::vec2 size);
			void SetScale(glm::vec2 scale);
			void SetSolor(glm::vec4 color);

			void Draw(glm::mat4 &projection);
		};
	}
}

#endif
