#include <Andromeda/Graphics/Sprite.h>

namespace Andromeda
{
	namespace Graphics
	{
		int Sprite::_objectCount = 0;

		Sprite::Sprite(std::string name, std::string imageName, std::string vertexShader, std::string fragmentShader)
		{
			_objectCount++;

			_name = name;

			//load shader
			_shader = ShaderManager::Instance()->LoadFromFile(name, vertexShader, fragmentShader, Textured);

			//load texture
			_texture = TextureManager::Instance()->LoadFromFile(imageName);

			//set size from texture
			
			if (_texture->Resized())
			{
				_size = glm::vec2(_texture->GetTextureWidth(), _texture->GetTextureHeight());
			}
			else
			{
				_size = glm::vec2(_texture->GetWidth(), _texture->GetHeight());
			}

			//color
			_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			//position
			_position = glm::vec2(0.0f, 0.0f);

			//
			_angle = 0.0f;

			_scale = glm::vec2(1.0f, 1.0f);

			//
			CreateVertexObject(false);
		}

		Sprite::Sprite(std::string name, std::string imageName, Shader* shader)
		{
			_objectCount++;

			_name = name;

			//load shader
			_shader = shader;

			//load texture
			_texture = TextureManager::Instance()->LoadFromFile(imageName);

			//set size from texture

			if (_texture->Resized())
			{
				_size = glm::vec2(_texture->GetTextureWidth(), _texture->GetTextureHeight());
			}
			else
			{
				_size = glm::vec2(_texture->GetWidth(), _texture->GetHeight());
			}

			//color
			_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			//position
			_position = glm::vec2(0.0f, 0.0f);

			//
			_angle = 0.0f;

			_scale = glm::vec2(1.0f, 1.0f);

			//
			CreateVertexObject(false);
		}

		Sprite::Sprite(std::string name, Texture* texture, Shader* shader)
		{
			_objectCount++;

			_name = name;

			//load shader
			_shader = shader;

			//load texture
			_texture = texture;

			//set size from texture
			if (_texture->Resized())
			{
				_size = glm::vec2(_texture->GetTextureWidth(), _texture->GetTextureHeight());
			}
			else
			{
				_size = glm::vec2(_texture->GetWidth(), _texture->GetHeight());
			}

			//color
			_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			//position
			_position = glm::vec2(0.0f, 0.0f);

			_angle = 0.0f;

			_scale = glm::vec2(1.0f, 1.0f);

			//
			CreateVertexObject(false);
		}

		Sprite::Sprite(std::string name, Texture* texture, Shader* shader, glm::vec2 location, glm::vec2 size)
		{
			_objectCount++;

			_name = name;

			//load shader
			_shader = shader;

			//load texture
			_texture = texture;

			//size
			_size = size;

			//location
			_location = location;

			//color
			_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			//position
			_position = glm::vec2(0.0f, 0.0f);

			_angle = 0.0f;

			_scale = glm::vec2(1.0f, 1.0f);

			//
			CreateVertexObject(true);
		}

		Sprite::~Sprite()
		{
			_objectCount--;
			delete _arrayObject;
		}

		void Sprite::SetShader(Shader* shader)
		{
			_shader = shader;
		}

		void Sprite::SetTexture(Texture* texture)
		{
			_texture = texture;
		}

		void Sprite::SetAngle(float angle)
		{
			_angle = angle;
		}

		void Sprite::SetPosition(glm::vec2 position)
		{
			_position = position;
		}

		void Sprite::SetSize(glm::vec2 size)
		{
			_size = size;

			UpdateSize();
		}

		void Sprite::SetScale(glm::vec2 scale)
		{
			_scale = scale;
		}

		void Sprite::SetSolor(glm::vec4 color)
		{
			_color = color;
		}

		void Sprite::Draw(glm::mat4 &projection)
		{
			//bind texture
			RenderManager::Instance()->UseTexture(_texture);

			//shader
			_shader->Bind();

			glm::mat4 model;
			glm::vec2 size = _size * _scale;

			model = glm::translate(model, glm::vec3(_position - (size / 2.0f), 0.0f));
			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
			model = glm::rotate(model, _angle, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
			model = glm::scale(model, glm::vec3(size, 1.0f));

			glm::mat4 translation = projection * model;

			_shader->SetUniform(VertexShader, "translation", translation);
			_shader->SetUniform(FragmentShader, "colors", _color);

			_arrayObject->Draw();
		}

		void Sprite::CreateVertexObject(bool customUV)
		{
			//create data buffer object
			_arrayObject = RenderManager::Instance()->CreateVertexArrayObject(Textured, StaticDraw);

			//create vertices
			_arrayObject->CreateVertices(4);

			//get vertices
			TextureVertex* _simpleData = static_cast<TextureVertex*>(_arrayObject->GetVertices());

			_simpleData[0].x = 0.0f;	_simpleData[0].y = 0.0f;	_simpleData[0].z = 0.0f;
			_simpleData[1].x = 0.0f;	_simpleData[1].y = 1.0f;	_simpleData[1].z = 0.0f;
			_simpleData[2].x = 1.0f;	_simpleData[2].y = 0.0f;	_simpleData[2].z = 0.0f;
			_simpleData[3].x = 1.0f;	_simpleData[3].y = 1.0f;	_simpleData[3].z = 0.0f;

			if (customUV)
			{
				float startX = (float)_location.x / (float)_texture->GetWidth();
				float endX = (float)(_location.x + _size.x) / (float)_texture->GetWidth();

				float startY = _location.y / (float)_texture->GetHeight();
				float endY = (float)(_location.y + _size.y) / (float)_texture->GetHeight();				

				_simpleData[0].u = startX;	_simpleData[0].v = startY;
				_simpleData[1].u = startX;	_simpleData[1].v = endY;
				_simpleData[2].u = endX;	_simpleData[2].v = startY;
				_simpleData[3].u = endX;	_simpleData[3].v = endY;
			}
			else
			{
				if (_texture->Resized())
				{
					float width = (float)_texture->GetTextureWidth() / (float)_texture->GetWidth();
					float height = (float)_texture->GetTextureHeight() / (float)_texture->GetHeight();

					_simpleData[0].u = 0.0f;			_simpleData[0].v = 0.0f;
					_simpleData[1].u = 0.0f;			_simpleData[1].v = 1.0f * height;
					_simpleData[2].u = 1.0f * width;	_simpleData[2].v = 0.0f;
					_simpleData[3].u = 1.0f * width;	_simpleData[3].v = 1.0f * height;
				}
				else
				{
					_simpleData[0].u = 0.0f;	_simpleData[0].v = 0.0f;
					_simpleData[1].u = 0.0f;	_simpleData[1].v = 1.0f;
					_simpleData[2].u = 1.0f;	_simpleData[2].v = 0.0f;
					_simpleData[3].u = 1.0f;	_simpleData[3].v = 1.0f;
				}				
			}

			//create indices
			_arrayObject->CreateIndices(6);

			//get indices
			unsigned short* _indices = static_cast<unsigned short*>(_arrayObject->GetIndices());

			//set data
			_indices[0] = 1;
			_indices[1] = 2;
			_indices[2] = 0;

			_indices[3] = 1;
			_indices[4] = 3;
			_indices[5] = 2;

			//generate buffer object
			_arrayObject->Generate();
		}

		void Sprite::UpdateSize()
		{
			TextureVertex* _simpleData = new TextureVertex[4];

			_simpleData[0].x = 0.0f;	_simpleData[0].y = 0.0f;	_simpleData[0].z = 0.0f;
			_simpleData[1].x = 0.0f;	_simpleData[1].y = 1.0f;	_simpleData[1].z = 0.0f;
			_simpleData[2].x = 1.0f;	_simpleData[2].y = 0.0f;	_simpleData[2].z = 0.0f;
			_simpleData[3].x = 1.0f;	_simpleData[3].y = 1.0f;	_simpleData[3].z = 0.0f;

			float width = _size.x / (float)_texture->GetWidth();
			float height = _size.y / (float)_texture->GetHeight();

			_simpleData[0].u = 0.0f;			_simpleData[0].v = 0.0f;
			_simpleData[1].u = 0.0f;			_simpleData[1].v = 1.0f * height;
			_simpleData[2].u = 1.0f * width;	_simpleData[2].v = 0.0f;
			_simpleData[3].u = 1.0f * width;	_simpleData[3].v = 1.0f * height;

			_arrayObject->UpdateVertices(_simpleData, 4);
		}
	}
}
