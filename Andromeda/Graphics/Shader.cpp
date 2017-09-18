#include <Andromeda/Graphics/Shader.h>

namespace Andromeda
{
	namespace Graphics
	{
		Shader::Shader()
		{
			_vertexShaderFile = "";
			_fragmentShaderFile = "";
		}

		void Shader::SetName(std::string name)
		{
			_name = name;
		}

		std::string Shader::GetName()
		{
			return _name;
		}

		Shader::~Shader()
		{

		}
	}
}
