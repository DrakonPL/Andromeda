#ifndef MemoryManagerGxm_H
#define MemoryManagerGxm_H

#include <Andromeda/System/MemoryManager.h>

namespace Andromeda
{
	namespace System
	{
		class MemoryManagerGxm : public MemoryManager
		{
		public:

			void AllocTexture(Graphics::Texture* texture);
			void FreeTexture(Graphics::Texture* texture);
		};
	}
}

#endif