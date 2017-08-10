#include <Andromeda/Graphics/Text/FontManager.h>

namespace Andromeda
{
	namespace Graphics
	{
		FontManager* FontManager::_manager = 0;

		FontManager::FontManager()
		{

		}

		FontManager* FontManager::Instance()
		{
			if (_manager == 0)
			{
				_manager = new FontManager();
			}

			return _manager;
		}
	}
}
