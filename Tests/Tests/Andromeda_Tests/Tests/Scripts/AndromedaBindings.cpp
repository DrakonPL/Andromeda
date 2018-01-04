#include "AndromedaBindings.h"

#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Sprite.h>

AndromedaBindings::AndromedaBindings(lua_State* state)
{
	_luaState = state;
}

AndromedaBindings::~AndromedaBindings()
{

}

void AndromedaBindings::Bind()
{
	BindGraphics();
}

void AndromedaBindings::BindGraphics()
{
	try
	{

	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::VertexType>("VertexType")
		.enum_("constants")
		[
			luabind::value("Color", Andromeda::Graphics::VertexType::Color),
			luabind::value("Simple", Andromeda::Graphics::VertexType::Simple),
			luabind::value("Textured", Andromeda::Graphics::VertexType::Textured),
			luabind::value("TextureNormal", Andromeda::Graphics::VertexType::TextureNormal),
			luabind::value("TextureColor", Andromeda::Graphics::VertexType::TextureColor),
			luabind::value("ColorNormal", Andromeda::Graphics::VertexType::ColorNormal),
			luabind::value("TextureColorNormal", Andromeda::Graphics::VertexType::TextureColorNormal)
		]
	];

	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::VertexPrimitive>("VertexPrimitive")
		.enum_("constants")
		[
			luabind::value("Triangle", Andromeda::Graphics::VertexPrimitive::Triangle),
			luabind::value("TriangleStrip", Andromeda::Graphics::VertexPrimitive::TriangleStrip),
			luabind::value("TriangleFan", Andromeda::Graphics::VertexPrimitive::TriangleFan),
			luabind::value("Lines", Andromeda::Graphics::VertexPrimitive::Lines)
		]
	];

	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::TextureFilerType>("TextureFilerType")
		.enum_("constants")
		[
			luabind::value("NearestFilter", 0),
			luabind::value("LinearFilter",1)
		]
	];

	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::TextureColorType>("TextureColorType")
		.enum_("constants")
		[
			luabind::value("Texture_RGBA", 0),
			luabind::value("Texture_RGB", 1),
			luabind::value("Texture_YVU420P2", 2)
		]
	];

	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::ShaderType>("ShaderType")
		.enum_("constants")
		[
			luabind::value("VertexShader", Andromeda::Graphics::ShaderType::VertexShader),
			luabind::value("FragmentShader", Andromeda::Graphics::ShaderType::FragmentShader)
		]
	];

	//texture
	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::Texture>("Texture")
		.def("LoadFromFile", &Andromeda::Graphics::Texture::LoadFromFile)
		.def("LoadFromMemory", &Andromeda::Graphics::Texture::LoadFromMemory)
		.def("Resized", &Andromeda::Graphics::Texture::Resized)
		.def("GetWidth", &Andromeda::Graphics::Texture::GetWidth)
		.def("GetHeight", &Andromeda::Graphics::Texture::GetHeight)
		.def("GetTextureWidth", &Andromeda::Graphics::Texture::GetTextureWidth)
		.def("GetTextureHeight", &Andromeda::Graphics::Texture::GetTextureHeight)
		.def("GetFilterType", &Andromeda::Graphics::Texture::GetFilterType)
		.def("GetColorType", &Andromeda::Graphics::Texture::GetColorType)
		.def("GetId", &Andromeda::Graphics::Texture::GetId)
	];

	//texture manager
	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::TextureManager>("TextureManager")
		.def("LoadFromFile", &Andromeda::Graphics::TextureManager::LoadFromFile)
		.def("LoadFromMemory", &Andromeda::Graphics::TextureManager::LoadFromMemory) //method to execute a lua script
		.def("Get", &Andromeda::Graphics::TextureManager::Get) //method to execute a lua script
		.def("Add", &Andromeda::Graphics::TextureManager::Add) //method to execute a lua script
		.def("Remove", (void(Andromeda::Graphics::TextureManager::*)(std::string))&Andromeda::Graphics::TextureManager::Remove) //method to execute a lua script
		.def("Remove", (void(Andromeda::Graphics::TextureManager::*)(Andromeda::Graphics::Texture*))&Andromeda::Graphics::TextureManager::Remove) //method to execute a lua script
		.def("RemoveAll", &Andromeda::Graphics::TextureManager::RemoveAll) //method to execute a lua script
		.scope
		[
			luabind::def("Instance", &Andromeda::Graphics::TextureManager::Instance)
		]
	];

	//shader
	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::Shader>("Shader")
		.def("GetName", &Andromeda::Graphics::Shader::GetName)
		.def("Bind", &Andromeda::Graphics::Shader::Bind)
		.def("LoadFromFile", &Andromeda::Graphics::Shader::LoadFromFile)
		.def("LoadFromMemory", &Andromeda::Graphics::Shader::LoadFromMemory)
		.def("SetUniform", (void(Andromeda::Graphics::Shader::*)(Andromeda::Graphics::ShaderType, std::string,int))&Andromeda::Graphics::Shader::SetUniform)
		.def("SetUniform", (void(Andromeda::Graphics::Shader::*)(Andromeda::Graphics::ShaderType, std::string, float))&Andromeda::Graphics::Shader::SetUniform)
		.def("SetUniform", (void(Andromeda::Graphics::Shader::*)(Andromeda::Graphics::ShaderType, std::string, glm::vec3 &))&Andromeda::Graphics::Shader::SetUniform)
		.def("SetUniform", (void(Andromeda::Graphics::Shader::*)(Andromeda::Graphics::ShaderType, std::string, glm::vec4 &))&Andromeda::Graphics::Shader::SetUniform)
		.def("SetUniform", (void(Andromeda::Graphics::Shader::*)(Andromeda::Graphics::ShaderType, std::string, glm::mat3 &))&Andromeda::Graphics::Shader::SetUniform)
		.def("SetUniform", (void(Andromeda::Graphics::Shader::*)(Andromeda::Graphics::ShaderType, std::string, glm::mat4 &))&Andromeda::Graphics::Shader::SetUniform)
	];

	//ShaderManager
	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::ShaderManager>("ShaderManager")
		.def("LoadFromFile", &Andromeda::Graphics::ShaderManager::LoadFromFile)
		.def("LoadFromMemory", &Andromeda::Graphics::ShaderManager::LoadFromMemory) //method to execute a lua script
		.def("Get", &Andromeda::Graphics::ShaderManager::Get) //method to execute a lua script
		.def("Remove", (void(Andromeda::Graphics::ShaderManager::*)(std::string))&Andromeda::Graphics::ShaderManager::Remove) //method to execute a lua script
		.def("Remove", (void(Andromeda::Graphics::ShaderManager::*)(Andromeda::Graphics::Shader*))&Andromeda::Graphics::ShaderManager::Remove) //method to execute a lua script
		.def("RemoveAll", &Andromeda::Graphics::ShaderManager::RemoveAll) //method to execute a lua script
		.scope
		[
			luabind::def("Instance", &Andromeda::Graphics::ShaderManager::Instance)
		]
	];

	//Sprite
	luabind::module(_luaState)
	[
		luabind::class_<Andromeda::Graphics::Sprite>("Sprite")
		.def(luabind::constructor<std::string, std::string, std::string, std::string>())
		.def(luabind::constructor<std::string, std::string, Andromeda::Graphics::Shader*>())
		.def(luabind::constructor<std::string, Andromeda::Graphics::Texture*, Andromeda::Graphics::Shader*>())
		.def(luabind::constructor<std::string, Andromeda::Graphics::Texture*, Andromeda::Graphics::Shader*, glm::vec2, glm::vec2>())
		.def("SetShader", &Andromeda::Graphics::Sprite::SetShader)
		.def("SetTexture", &Andromeda::Graphics::Sprite::SetTexture)
		.def("SetAngle", &Andromeda::Graphics::Sprite::SetAngle)
		.def("SetPosition", &Andromeda::Graphics::Sprite::SetPosition)
		.def("SetSize", &Andromeda::Graphics::Sprite::SetSize)
		.def("SetScale", &Andromeda::Graphics::Sprite::SetScale)
		.def("SetSolor", &Andromeda::Graphics::Sprite::SetSolor)
		.def("Draw", &Andromeda::Graphics::Sprite::Draw)
	];

	}
	catch (const std::exception &TheError)
	{
		std::string erro = TheError.what();
	}
}