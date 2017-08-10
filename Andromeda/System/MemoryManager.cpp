#include <Andromeda/System/MemoryManager.h>

#ifdef ANDROMEDA_GLFW
#include <Andromeda/System/GLFW/MemoryManagerGlfw.h>
#endif

#ifdef ANDROMEDA_VITA
#include <Andromeda/System/GXM/MemoryManagerGxm.h>
#endif

#ifdef ANDROMEDA_RPI
#include <Andromeda/System/RPI/MemoryManagerRpi.h>
#endif

namespace Andromeda
{
	namespace System
	{
		MemoryManager* MemoryManager::_memoryManager = 0;

		MemoryManager::MemoryManager()
		{

		}

		MemoryManager* MemoryManager::Instance()
		{
			if (_memoryManager == 0	)
			{
				#ifdef ANDROMEDA_GLFW
				{
					_memoryManager = new MemoryManagerGlfw();
				}
				#endif

				#ifdef ANDROMEDA_VITA
				{
					_memoryManager = new MemoryManagerGxm();
				}
				#endif
				
				#ifdef ANDROMEDA_RPI
				{
					_memoryManager = new MemoryManagerRpi();
				}
				#endif
			}

			return _memoryManager;
		}
	}
}
