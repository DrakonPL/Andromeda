#ifndef FontManager_H
#define FontManager_H

namespace Andromeda
{
	namespace Graphics
	{
		class FontManager
		{
		private:

			static FontManager* _manager;

			FontManager();

		public:

			static FontManager* Instance();
		};
	}
}

#endif