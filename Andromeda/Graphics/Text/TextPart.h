#ifndef TextPart_H
#define TextPart_H

#include <string>
#include <glm/glm.hpp>
#include <Andromeda/Graphics/Texture.h>

namespace Andromeda
{
	namespace Graphics
	{
		class TextPart
		{
		public:

			std::string Text;
			glm::vec2 Position;
			glm::vec3 Color;
			TextureFontAlign FontAlign;
		};
	}
}

#endif
