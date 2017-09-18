#ifndef Shader_H
#define Shader_H

#include <Andromeda/Graphics/GraphicsEnums.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Andromeda
{
	namespace Graphics
	{
		class ShaderManager;

		class Shader
		{
		protected:

			std::string _name;

			std::string _vertexShaderFile;
			std::string _fragmentShaderFile;

			VertexType _vertexType;

			Shader();

			void SetName(std::string name);

		public :		

			virtual ~Shader();

			//
			std::string GetName();

			//use this current shader
			virtual void Bind() = 0;

			//load shader from file or from text
			virtual void LoadFromFile(std::string vertexFile, std::string fragmentFile, VertexType vertexType) = 0;
			virtual void LoadFromMemory(std::string vertexShader, std::string fragmentShader, VertexType vertexType) = 0;

			//set uniforms values
			virtual void SetUniform(ShaderType shaderType, std::string name, int val) = 0;
			virtual void SetUniform(ShaderType shaderType, std::string name, float val) = 0;
			virtual void SetUniform(ShaderType shaderType, std::string name, glm::vec3 & val) = 0;
			virtual void SetUniform(ShaderType shaderType, std::string name, glm::vec4 & val) = 0;
			virtual void SetUniform(ShaderType shaderType, std::string name, glm::mat3 & val) = 0;
			virtual void SetUniform(ShaderType shaderType, std::string name, glm::mat4 & val) = 0;

			friend class ShaderManager;
		};
	}
}

#endif
