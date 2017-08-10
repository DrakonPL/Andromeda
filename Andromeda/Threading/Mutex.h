#ifndef Mutex_H
#define Mutex_H

#include <Andromeda/Threading/BaseMutex.h>

namespace Andromeda
{
	namespace Threading
	{
		class Mutex
		{
		private:

			BaseMutex* _mutex;

		public:

			Mutex();
			~Mutex();

			void Lock();
			void Unlock();
		};
	}
}

#endif
