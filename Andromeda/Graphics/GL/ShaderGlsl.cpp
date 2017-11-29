#include <Andromeda/Graphics/GL/ShaderGlsl.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <Andromeda/Utils/Logger.h>

#define GLEW_STATIC
#include <GL/glew.h>

namespace Andromeda
{
	namespace Graphics
	{
		ShaderGlSl::ShaderGlSl() : Shader()
		{
			_shaderProgram = -1;

			_vertexShader = -1;
			_fragmentShader = -1;
		}

		ShaderGlSl::~ShaderGlSl()
		{
			glDeleteProgram(_shaderProgram);
		}
		
		void ShaderGlSl::LoadFromFile(std::string vertexFile, std::string fragmentFile, VertexType vertexType)
		{
			_vertexType = vertexType;

			//load vertex shader
			_vertexShader = LoadShaderFile(vertexFile, VertexShader);

			//load fragment shader
			_fragmentShader = LoadShaderFile(fragmentFile, FragmentShader);

			//link program
			_shaderProgram = LinkShader(_vertexShader, _fragmentShader);
		}

		void ShaderGlSl::LoadFromMemory(std::string vertexShader, std::string fragmentShader, VertexType vertexType)
		{
			_vertexType = vertexType;

			//load vertex shader
			_vertexShader = LoadShaderText(vertexShader, VertexShader);

			//load fragment shader
			_fragmentShader = LoadShaderText(fragmentShader, FragmentShader);

			//ling program
			_shaderProgram = LinkShader(_vertexShader, _fragmentShader);
		}

		void ShaderGlSl::Bind()
		{
			glUseProgram(_shaderProgram);
		}

		unsigned int ShaderGlSl::LoadShaderFile(std::string fileName, ShaderType shaderType)
		{
			//load shader file
			FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(fileName);

			if (file == 0)
				return -1;

			file->Open(FileSystem::Read, FileSystem::Binary);

			int dataSize = 0;
			const char* shaderCode = file->GetTextData(dataSize);

			file->Close();
			delete file;


			unsigned int shader = -1;

			//create shader
			if (shaderType == VertexShader)
			{
				shader = glCreateShader(GL_VERTEX_SHADER);
			}
			else
			{
				shader = glCreateShader(GL_FRAGMENT_SHADER);
			}

			//set source of shader
			glShaderSource(shader, 1, &shaderCode, NULL);

			//compile shader
			glCompileShader(shader);

			//check for compilation errors
			GLint success;
			GLchar infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				Utils::Logger_Info("Shader: %s compilation error: %s\n", fileName, infoLog);
			}

			//delete text
			delete[] shaderCode;

			return shader;
		}

		unsigned int ShaderGlSl::LoadShaderText(std::string shaderString, ShaderType shaderType)
		{
			const char* shaderCode = shaderString.c_str();
			
			unsigned int shader = -1;

			//create shader
			if(shaderType == VertexShader)
			{
				shader = glCreateShader(GL_VERTEX_SHADER);
			}
			else
			{
				shader = glCreateShader(GL_FRAGMENT_SHADER);
			}
			
			//set source of shader
			glShaderSource(shader, 1, &shaderCode, NULL);
			
			//compile shader
			glCompileShader(shader);

			//check for compilation errors
			GLint success;
			GLchar infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				Utils::Logger_Info("Shader: %s compilation error: %s\n", shaderString.c_str(), infoLog);
			}

			return shader;
		}

		unsigned int ShaderGlSl::LinkShader(unsigned int vertexShader, unsigned int fragmentShader)
		{
			//create new shader programs
			unsigned int shaderProgram = glCreateProgram();

			//attach vertex and fragment shaders
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);

			//link program
			glLinkProgram(shaderProgram);

			//check for compilation errors
			GLint success;
			GLchar infoLog[512];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
				Utils::Logger_Info("Shader link error: %s\n", infoLog);
			}

			//detach shader
			glDetachShader(shaderProgram, vertexShader);
			glDetachShader(shaderProgram, fragmentShader);

			//delete shaders
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return shaderProgram;
		}

		void ShaderGlSl::SetUniform(ShaderType shaderType, std::string name, int val)
		{
			GLint uniformLocation = glGetUniformLocation(_shaderProgram, name.c_str());
			glUniform1i(uniformLocation, val);
		}

		void ShaderGlSl::SetUniform(ShaderType shaderType, std::string name, float val)
		{
			GLint uniformLocation = glGetUniformLocation(_shaderProgram, name.c_str());
			glUniform1f(uniformLocation, val);
		}

		void ShaderGlSl::SetUniform(ShaderType shaderType, std::string name, glm::vec3& val)
		{
			GLint uniformLocation = glGetUniformLocation(_shaderProgram, name.c_str());
			glProgramUniform3fv(_shaderProgram, uniformLocation, 1, glm::value_ptr(val));
		}

		void ShaderGlSl::SetUniform(ShaderType shaderType, std::string name, glm::vec4& val)
		{
			GLint uniformLocation = glGetUniformLocation(_shaderProgram, name.c_str());
			glProgramUniform4fv(_shaderProgram, uniformLocation, 1, glm::value_ptr(val));
		}

		void ShaderGlSl::SetUniform(ShaderType shaderType, std::string name, glm::mat3& val)
		{
			GLint uniformLocation = glGetUniformLocation(_shaderProgram, name.c_str());
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
		}

		void ShaderGlSl::SetUniform(ShaderType shaderType, std::string name, glm::mat4& val)
		{
			GLint uniformLocation = glGetUniformLocation(_shaderProgram, name.c_str());
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
		}
	}
}

