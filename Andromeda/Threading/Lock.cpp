#include <Andromeda/Threading/Lock.h>
#include <Andromeda/Threading/Mutex.h>


namespace Andromeda
{
	namespace Threading
	{
		Lock::Lock(Mutex& mutex) :_mutex(mutex)
		{
			_mutex.Lock();
		}

		Lock::~Lock()
		{
			_mutex.Unlock();
		}
	}
}
