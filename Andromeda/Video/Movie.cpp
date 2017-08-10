#include <Andromeda/Video/Movie.h>

namespace Andromeda
{
	namespace Video
	{

		Movie::Movie(std::string name)
		{
			_name = name;

			_volume = 1.0f;

			_looped = false;
			_loaded = false;
			_stream = false;
			_screenChanged = false;
		}

		Movie::Movie(std::string name, glm::vec2 position, glm::vec2 size)
		{
			_name = name;

			_srcPosition = position;
			_srcSize = size;

			_volume = 1.0f;

			_looped = false;
			_loaded = false;
			_stream = false;
			_screenChanged = true;
		}

		Movie::~Movie()
		{

		}

		void Movie::SetVolume(float volume)
		{
			_volume = volume;
		}

		void Movie::SetLoop(bool state)
		{
			_looped = state;
		}
	}
}
