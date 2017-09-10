#include <Andromeda/Graphics/Text/TexturedFont.h>
#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/FileSystem/FileManager.h>

#include <functional>


namespace Andromeda
{
	namespace Graphics
	{
		TexturedFont::TexturedFont(TextureAtlas* atlas, int size, std::string filename)
		{
			_atlas = atlas;
			_shader = 0;
			_vertexArray = 0;
			_fontAlign = FontCenter;

			_lastLenght = 0;
			_lastHash = 0;
			_maxLenght = 0;

			_text = "";
			_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			_position = glm::vec2(0.0f,0.0f);

			FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(filename.c_str());

			if (file == 0)
				return;

			file->Open(FileSystem::Read, FileSystem::Binary);

			int dataSize = 0;
			_buffer = file->GetData(dataSize);

			file->Close();
			delete file;

			//load actual data from memory
			LoadFromMemory(size, _buffer, dataSize);
		}

		TexturedFont::~TexturedFont()
		{
			//delete font structure
			texture_font_delete(_font);

			delete[] _buffer;

			//delete vertex buffer
			delete _vertexArray;
		}

		void TexturedFont::LoadFromMemory( int size, void* memory_font, size_t memory_size)
		{
			_font = texture_font_new_from_memory(_atlas->GetAtlas(), size, memory_font, memory_size);
		}

		void TexturedFont::CreateVertexObject()
		{
			//create
			_vertexArray = RenderManager::Instance()->CreateVertexArrayObject(TextureColor, DynamicDraw);

			_vertexArray->CreateVertices(4);
			_vertexArray->CreateIndices(6);

			TextureColorVertex* _simpleData = static_cast<TextureColorVertex*>(_vertexArray->GetVertices());
			unsigned short* _indices = static_cast<unsigned short*>(_vertexArray->GetIndices());

			_simpleData[0].x = 0.0f;	_simpleData[0].y = 0.0f;	_simpleData[0].z = 0.0f;
			_simpleData[1].x = 0.0f;	_simpleData[1].y = 0.0f;	_simpleData[1].z = 0.0f;
			_simpleData[2].x = 0.0f;	_simpleData[2].y = 0.0f;	_simpleData[2].z = 0.0f;
			_simpleData[3].x = 0.0f;	_simpleData[3].y = 0.0f;	_simpleData[3].z = 0.0f;

			_simpleData[0].r = 1.0f;	_simpleData[0].g = 1.0f;	_simpleData[0].b = 1.0f;
			_simpleData[1].r = 1.0f;	_simpleData[1].g = 1.0f;	_simpleData[1].b = 1.0f;
			_simpleData[2].r = 1.0f;	_simpleData[2].g = 1.0f;	_simpleData[2].b = 1.0f;
			_simpleData[3].r = 1.0f;	_simpleData[3].g = 1.0f;	_simpleData[3].b = 1.0f;

			_simpleData[0].u = 0.0f;	_simpleData[0].v = 0.0f;
			_simpleData[1].u = 0.0f;	_simpleData[1].v = 0.0f;
			_simpleData[2].u = 0.0f;	_simpleData[2].v = 0.0f;
			_simpleData[3].u = 0.0f;	_simpleData[3].v = 0.0f;

			//set data
			_indices[0] = 0;
			_indices[1] = 1;
			_indices[2] = 2;
			_indices[3] = 0;
			_indices[4] = 2;
			_indices[5] = 3;

			//generate buffer object
			_vertexArray->Generate();
		}



		int TexturedFont::CacheGlyphs(std::string text)
		{
			return texture_font_load_glyphs(_font, text.c_str());
		}

		void TexturedFont::SetShader(Shader* shader)
		{
			_shader = shader;
		}

		void TexturedFont::SetAlign(TextureFontAlign fontAlign)
		{
			_fontAlign = fontAlign;
		}

		void TexturedFont::SetPosition(glm::vec2 position)
		{
			_position = position;
		}

		void TexturedFont::SetSolor(glm::vec4 color)
		{
			_color = color;
		}

		void TexturedFont::SetText(std::string text)
		{
			_text = text;
		}

		void TexturedFont::AddText(std::string text, int x, int y, TextureFontAlign align)
		{
			TextPart part;
			part.Text = text;
			part.Position = glm::vec2(x, y);
			part.Color = glm::vec3(1.0f, 1.0f, 1.0f);
			part.FontAlign = align;

			_textParts.push_back(part);
		}

		void TexturedFont::AddText(std::string text, int x, int y, glm::vec3 color, TextureFontAlign align)
		{
			TextPart part;
			part.Text = text;
			part.Position = glm::vec2(x, y);
			part.Color = color;
			part.FontAlign = align;

			_textParts.push_back(part);
		}

		void TexturedFont::AddText(std::string text, glm::vec2 position, glm::vec3 color, TextureFontAlign align)
		{
			TextPart part;
			part.Text = text;
			part.Position = position;
			part.Color = color;
			part.FontAlign = align;

			_textParts.push_back(part);
		}

		int TexturedFont::GetTextLenght(std::string text)
		{
			int lenght = 0;

			const char * chartext = text.c_str();
			int charCount = text.length();

			for (int i = 0; i < charCount; i++)
			{
				texture_glyph_t *glyph = texture_font_get_glyph(_font, chartext + i);
				if (glyph != NULL)
				{
					float kerning = 0.0f;
					if (i > 0)
					{
						kerning = texture_glyph_get_kerning(glyph, chartext + i - 1);
					}

					lenght += kerning;
					lenght += glyph->advance_x;
				}
			}


			return lenght;
		}

		void TexturedFont::PrepareBuffer()
		{
			//get text lenght
			int textLenght = 0;
			int textHash = 0;
			float colorHash = 0.0f;
			float positionHash = 0.0f;
			_draw = true;

			std::string wholeText;

			for (int i = 0;i < _textParts.size();i++)
			{
				textLenght += _textParts[i].Text.length();
				wholeText += _textParts[i].Text;
				colorHash += _textParts[i].Color.x + _textParts[i].Color.y + _textParts[i].Color.z;
				positionHash += _textParts[i].Position.x + _textParts[i].Position.y;
			}

			if (textLenght == 0)
			{
				_draw = false;

				_lastHash = 0;
				_lastLenght = 0;
				_lastColour = 0;
				_lastPosition = 0;
				return;
			}

			std::hash<std::string> str_hash;
			textHash = str_hash(wholeText);

			//check size
			bool checkSize = _lastLenght != textLenght;
			bool checkHash = _lastHash != textHash;
			bool checkColor = _lastColour != colorHash;
			bool checkPosition = _lastPosition != positionHash;
			bool bufferNull = _vertexArray == 0;
			bool update = false;

			if(checkHash || checkSize || bufferNull || checkColor || checkPosition)
			{
				TextureColorVertex* _simpleData;
				unsigned short* _indices;

				int verts = textLenght * 4;
				int indices = textLenght * 6;

				//different hash or size but buffer exists
				if ((checkHash || checkSize || checkColor || checkPosition) && !bufferNull)
				{
					if (textLenght > _maxLenght)
					{
						//delete and create bigger buffer
						delete _vertexArray;
						_vertexArray = 0;

						bufferNull = true;
					}
					else
					{
						//update existing buffer
						_simpleData = new TextureColorVertex[verts];
						update = true;
					}
				}

				//if array is null
				if(bufferNull)
				{
					_vertexArray = RenderManager::Instance()->CreateVertexArrayObject(TextureColor, DynamicDraw);

					//verts and indices count
					_vertexArray->CreateVertices(verts);
					_vertexArray->CreateIndices(indices);

					_simpleData = static_cast<TextureColorVertex*>(_vertexArray->GetVertices());
					_indices = static_cast<unsigned short*>(_vertexArray->GetIndices());
				}

				int verCount = 0;
				int indiConut = 0;

				for (int i = 0; i < _textParts.size(); i++)
				{
					const char * text = _textParts[i].Text.c_str();
					int charCount = _textParts[i].Text.length();
					int textLenght = GetTextLenght(_textParts[i].Text);

					glm::vec2 position;
					glm::vec3 color = _textParts[i].Color;

					//get text start position based on align
					if (_textParts[i].FontAlign == FontLeft)
					{
						position = _textParts[i].Position;
					}

					if (_textParts[i].FontAlign == FontCenter)
					{
						position = glm::vec2(_textParts[i].Position.x - (textLenght / 2), _textParts[i].Position.y);
					}

					if (_textParts[i].FontAlign == FontRight)
					{
						position = glm::vec2(_textParts[i].Position.x - textLenght, _textParts[i].Position.y);
					}

					//add vertices for this text
					for (int c = 0; c < charCount; c++)
					{
						texture_glyph_t *glyph = texture_font_get_glyph(_font, text + c);
						if (glyph != NULL)
						{
							float kerning = 0.0f;
							if (c > 0)
							{
								kerning = texture_glyph_get_kerning(glyph, text + c - 1);
							}

							position.x += kerning;

							int x0 = (int)(position.x + glyph->offset_x);
							int y0 = (int)(position.y - glyph->offset_y);
							int x1 = (int)(x0 + glyph->width);
							int y1 = (int)(y0 + glyph->height);

							float s0 = glyph->s0;
							float t0 = glyph->t0;
							float s1 = glyph->s1;
							float t1 = glyph->t1;

							_simpleData[verCount + 0].x = x0;	_simpleData[verCount + 0].y = y0;	_simpleData[verCount + 0].z = 0.0f;
							_simpleData[verCount + 1].x = x0;	_simpleData[verCount + 1].y = y1;	_simpleData[verCount + 1].z = 0.0f;
							_simpleData[verCount + 2].x = x1;	_simpleData[verCount + 2].y = y1;	_simpleData[verCount + 2].z = 0.0f;
							_simpleData[verCount + 3].x = x1;	_simpleData[verCount + 3].y = y0;	_simpleData[verCount + 3].z = 0.0f;

							_simpleData[verCount + 0].u = s0;	_simpleData[verCount + 0].v = t0;
							_simpleData[verCount + 1].u = s0;	_simpleData[verCount + 1].v = t1;
							_simpleData[verCount + 2].u = s1;	_simpleData[verCount + 2].v = t1;
							_simpleData[verCount + 3].u = s1;	_simpleData[verCount + 3].v = t0;

							_simpleData[verCount + 0].r = color.x;	_simpleData[verCount + 0].g = color.y;	_simpleData[verCount + 0].b = color.z;
							_simpleData[verCount + 1].r = color.x;	_simpleData[verCount + 1].g = color.y;	_simpleData[verCount + 1].b = color.z;
							_simpleData[verCount + 2].r = color.x;	_simpleData[verCount + 2].g = color.y;	_simpleData[verCount + 2].b = color.z;
							_simpleData[verCount + 3].r = color.x;	_simpleData[verCount + 3].g = color.y;	_simpleData[verCount + 3].b = color.z;

							position.x += glyph->advance_x;

							if (!update)
							{
								_indices[indiConut + 0] = verCount + 0;
								_indices[indiConut + 1] = verCount + 1;
								_indices[indiConut + 2] = verCount + 2;
								_indices[indiConut + 3] = verCount + 0;
								_indices[indiConut + 4] = verCount + 2;
								_indices[indiConut + 5] = verCount + 3;

								indiConut += 6;
							}

							verCount += 4;
						}
					}
				}

				if (update)
				{
					_vertexArray->UpdateVertices(_simpleData, verts);
					_vertexArray->SetIndicesNumber(indices);
				}
				else
				{
					_vertexArray->Generate();
				}
			}

			_lastHash = textHash;
			_lastLenght = textLenght;
			_lastColour = colorHash;
			_lastPosition = positionHash;

			if(textLenght > _maxLenght)
			{
				_maxLenght = textLenght;
			}			
		}

		void TexturedFont::Draw(glm::mat4 &projection)
		{
			PrepareBuffer();

			if (_draw == true && _vertexArray != 0 && _atlas != 0 && _shader != 0)
			{
				//bind texture
				RenderManager::Instance()->UseTexture(_atlas->GetTexture());

				//shader
				_shader->Bind();

				_shader->SetUniform(VertexShader, "translation", projection);
				//_shader->SetUniform(FragmentShader, "colors", _color);

				_vertexArray->Draw();
			}

			_textParts.clear();
		}

		void TexturedFont::Draw(glm::mat4 &projection, std::string text, int x, int y, TextureFontAlign align)
		{
			SetText(text);
			SetPosition(glm::vec2(x, y));
			SetAlign(align);
			Draw(projection);
		}
	}
}