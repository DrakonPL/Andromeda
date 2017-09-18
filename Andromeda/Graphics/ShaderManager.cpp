#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Utils/Logger.h>

namespace Andromeda
{
	namespace Graphics
	{
		ShaderManager* ShaderManager::_shaderManager = 0;

		ShaderManager::ShaderManager()
		{
			
		}

		ShaderManager* ShaderManager::Instance()
		{
			if(_shaderManager == 0)
			{
				_shaderManager = new ShaderManager();
			}

			return _shaderManager;
		}

		Shader* ShaderManager::LoadFromFile(std::string name, std::string vertexFile, std::string fragmentFile, VertexType vertexType)
		{
			if (_shaders.find(name) == _shaders.end())
			{
				Shader* shader = RenderManager::Instance()->CreateShader();

				//set name
				shader->SetName(name);

				//here change name based on platform
				vertexFile = vertexFile + RenderManager::Instance()->GetVertexShaderName();
				fragmentFile = fragmentFile + RenderManager::Instance()->GetFragmnetShaderName();

				//load shader
				shader->LoadFromFile(vertexFile, fragmentFile, vertexType);

				//add to collection
				_shaders.insert(std::pair<std::string, Shader*>(name, shader));

				return shader;
			}

			return _shaders[name];
		}

		Shader* ShaderManager::LoadFromMemory(std::string name, std::string vertexShader, std::string fragmentShader, VertexType vertexType)
		{
			if (_shaders.find(name) == _shaders.end())
			{
				Shader* shader = RenderManager::Instance()->CreateShader();

				//set name
				shader->SetName(name);

				//load shader
				shader->LoadFromMemory(vertexShader, fragmentShader, vertexType);

				//add to collection
				_shaders.insert(std::pair<std::string, Shader*>(name, shader));

				return shader;
			}

			return _shaders[name];
		}

		Shader* ShaderManager::Get(std::string name)
		{
			if (_shaders.find(name) == _shaders.end())
			{
				return 0;
			}

			return _shaders[name];
		}

		void ShaderManager::Remove(std::string name)
		{
			std::map<std::string, Shader*>::iterator it = _shaders.find(name);

			if (it == _shaders.end())
			{
				return;
			}

			delete _shaders[name];
			_shaders.erase(it);
		}

		void ShaderManager::Remove(Shader* shader)
		{
			Remove(shader->GetName());
		}

		void ShaderManager::RemoveAll()
		{
			std::map<std::string, Shader*>::iterator iter;

			for (iter = _shaders.begin(); iter != _shaders.end(); ++iter)
			{
				Utils::Logger_Info("Delete shader: %s \n", iter->first.c_str());
				delete iter->second;
			}

			_shaders.clear();
		}
	}
}
