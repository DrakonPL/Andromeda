#include <Andromeda/Threading/Mutex.h>

#ifdef ANDROMEDA_PC
#include <Andromeda/Threading/Win32/WinMutex.h>
#endif

namespace Andromeda
{
	namespace Threading
	{
		Mutex::Mutex()
		{
			#ifdef ANDROMEDA_PC
			_mutex = new WinMutex();
			#endif
		}

		Mutex::~Mutex()
		{
			delete _mutex;
		}

		void Mutex::Lock()
		{
			_mutex->Lock();
		}

		void Mutex::Unlock()
		{
			_mutex->Unlock();
		}
	}
}