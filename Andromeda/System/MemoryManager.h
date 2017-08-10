#ifndef MemoryManager_H
#define MemoryManager_H

#include <Andromeda/Graphics/Texture.h>

namespace Andromeda
{
	namespace System
	{
		class MemoryManager
		{
		protected:

			static MemoryManager *_memoryManager;

			MemoryManager();

		public:

			static MemoryManager* Instance();

			virtual void AllocTexture(Graphics::Texture* texture) = 0;
			virtual void FreeTexture(Graphics::Texture* texture) = 0;
		};
	}
}

#endif