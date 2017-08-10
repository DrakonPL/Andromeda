#ifndef ShaderManager_H
#define ShaderManager_H

#include <Andromeda/Graphics/Shader.h>
#include <map>


namespace Andromeda
{
	namespace Graphics
	{
		class ShaderManager
		{
		private:

			static ShaderManager* _shaderManager;
			std::map<std::string, Shader*> _shaders;

			ShaderManager();

		public:

			static ShaderManager* Instance();

			Shader* LoadFromFile(std::string name, std::string vertexFile, std::string fragmentFile, VertexType vertexType);
			Shader* LoadFromMemory(std::string name, std::string vertexShader, std::string fragmentShader, VertexType vertexType);

			Shader* Get(std::string name);

			void Remove(std::string name);
			void RemoveAll();
		};
	}
}

#endif
