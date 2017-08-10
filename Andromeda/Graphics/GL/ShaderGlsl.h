#ifndef GlslShader_H
#define GlslShader_H

#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>

namespace Andromeda
{
	namespace Graphics
	{
		class ShaderGlSl : public Shader
		{
		
		protected:

			unsigned int _shaderProgram; 
			unsigned int _vertexShader;
			unsigned int _fragmentShader;

			unsigned int LoadShaderFile(std::string fileName,ShaderType shaderType);
			unsigned int LoadShaderText(std::string shader,ShaderType shaderType);

			unsigned int LinkShader(unsigned int vertexShader, unsigned int fragmentShader);

		public:

			ShaderGlSl();
			~ShaderGlSl();

			void LoadFromFile(std::string vertexFile, std::string fragmentFile, VertexType vertexType);
			void LoadFromMemory(std::string vertexShader, std::string fragmentShader, VertexType vertexType);

			void Bind();

			void SetUniform(ShaderType shaderType, std::string name, int val);
			void SetUniform(ShaderType shaderType, std::string name, float val);
			void SetUniform(ShaderType shaderType, std::string name, glm::vec3& val);
			void SetUniform(ShaderType shaderType, std::string name, glm::vec4& val);
			void SetUniform(ShaderType shaderType, std::string name, glm::mat3& val);
			void SetUniform(ShaderType shaderType, std::string name, glm::mat4& val);
		};
	}
}

#endif
