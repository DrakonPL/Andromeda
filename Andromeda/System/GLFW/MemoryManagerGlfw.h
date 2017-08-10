#ifndef MemoryManagerGlfw_H
#define MemoryManagerGlfw_H

#include <Andromeda/System/MemoryManager.h>

namespace Andromeda
{
	namespace System
	{
		class MemoryManagerGlfw : public MemoryManager
		{
		public:

			void AllocTexture(Graphics::Texture* texture);
			void FreeTexture(Graphics::Texture* texture);
		};
	}
}

#endif