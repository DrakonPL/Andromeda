#ifndef DynamicTextureFont_H
#define DynamicTextureFont_H

#include <Andromeda/Graphics/Text/TextureAtlas.h>
#include <Andromeda/Graphics/VertexArrayObject.h>
#include <Andromeda/Graphics/Shader.h>

#include <string>
#include <texture-font.h>
#include <vector>
#include "TextPart.h"
using namespace ftgl;

#include <glm/glm.hpp>

namespace Andromeda
{
	namespace Graphics
	{
		class TexturedFont
		{
		private:

			//ftgl font
			texture_font_t* _font;

			//atlas
			TextureAtlas* _atlas;

			//vertex array
			VertexArrayObject* _vertexArray;

			//memory buffer
			unsigned char* _buffer;

			//shader
			Shader* _shader;

			TextureFontAlign _fontAlign;

			std::string _text;

			glm::vec2 _position;
			glm::vec4 _color;

			glm::mat4* _projection;

			std::vector<TextPart> _textParts;
			
			int _lastLenght;
			int _maxLenght;
			float _lastColour;
			float _lastPosition;
			size_t _lastHash;

			bool _draw;

			private:

			//load font from memory
			void LoadFromMemory(float size, void* memory_font, size_t memory_size);
			
			//create vertex array object
			void CreateVertexObject();

			float GetTextLenght(std::string text);

			void PrepareBuffer();

		public:

			TexturedFont(TextureAtlas* atlas, float size, std::string filename);
			~TexturedFont();

			int CacheGlyphs(std::string cache);

			void SetShader(Shader* shader);

			void SetAlign(TextureFontAlign fontAlign);

			void SetPosition(glm::vec2 position);
			void SetSolor(glm::vec4 color);
			void SetText(std::string text);

			void AddText(std::string text, int x, int y, TextureFontAlign align);
			void AddText(std::string text, int x, int y, glm::vec3 color, TextureFontAlign align);
			void AddText(std::string text, glm::vec2 position, glm::vec3 color, TextureFontAlign align);

			void Draw(glm::mat4 &projection);
			void Draw(glm::mat4 &projection, std::string text, int x, int y, TextureFontAlign align);
		};
	}
}

#endif
