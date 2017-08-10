#ifndef ShaderGxm_H
#define ShaderGxm_H

#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>

#include <psp2/gxm.h>

namespace Andromeda
{
	namespace Graphics
	{
		class ShaderGxm : public Shader
		{
		protected:

			SceGxmShaderPatcher* _shaderPatcher;
			SceGxmContext* _gxmContext;

			SceGxmProgram* _gxmVertexProgram;
			SceGxmProgram* _gxmFragmentProgram;

			//shader patchers id's
			SceGxmShaderPatcherId _vertexProgramId;
			SceGxmShaderPatcherId _fragmentProgramId;

			//shader programs
			SceGxmVertexProgram* _vertexProgram;
			SceGxmFragmentProgram* _fragmentProgram;

			unsigned int LoadShaderFile(std::string fileName, ShaderType shaderType);
			unsigned int LinkShader();

			const SceGxmProgramParameter *GetUniform(SceGxmShaderPatcherId programId, std::string paramName);

		public:

			ShaderGxm();
			~ShaderGxm();
			
			void LoadFromFile(std::string vertexFile, std::string fragmentFile, VertexType vertexType);
			void LoadFromMemory(std::string vertexShader, std::string fragmentShader, VertexType vertexType);

			void SetShaderPatcher(SceGxmShaderPatcher* shaderPatcher);
			void SetGxmContext(SceGxmContext* gxmContext);

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
