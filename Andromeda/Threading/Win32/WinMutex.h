#ifndef WinMutex_H
#define WinMutex_H

#include <Andromeda/Threading/BaseMutex.h>
#include <windows.h>

namespace Andromeda
{
	namespace Threading
	{
		class WinMutex : public BaseMutex
		{

		private:

			CRITICAL_SECTION _mutex;

		public:

			WinMutex();
			~WinMutex();

			void Lock();
			void Unlock();

		};
	}
}

#endif
