#include <Andromeda/Threading/Win32/WinMutex.h>

namespace Andromeda
{
	namespace Threading
	{
		WinMutex::WinMutex()
		{
			InitializeCriticalSection(&_mutex);
		}

		WinMutex::~WinMutex()
		{
			DeleteCriticalSection(&_mutex);
		}

		void WinMutex::Lock()
		{
			EnterCriticalSection(&_mutex);
		}

		void WinMutex::Unlock()
		{
			LeaveCriticalSection(&_mutex);
		}
	}
}