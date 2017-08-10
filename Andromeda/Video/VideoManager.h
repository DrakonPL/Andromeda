#ifndef VideoManager_H
#define VideoManager_H

#include <Andromeda/Video/Movie.h>

#include <string>
#include <vector>

namespace Andromeda
{
	namespace Video
	{
		class VideoManager
		{
		protected:

			std::vector<Movie*> _movies;

			static VideoManager *_videoManager;

		public:

			VideoManager();
			virtual ~VideoManager();

			static VideoManager* Instance();

		public:

			std::vector<Movie*> GetMovies() { return _movies; }

			virtual bool Init() = 0;

			virtual Movie* GetMovie(std::string name) = 0;
			virtual Movie* GetMovie(std::string name, glm::vec2 position, glm::vec2 size) = 0;

			virtual void Update(float dt) = 0;
		};
	}
}

#endif