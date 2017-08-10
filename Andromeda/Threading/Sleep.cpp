#include <Andromeda/Threading/Sleep.h>

#ifdef ANDROMEDA_PC
#include <Andromeda/Threading/Win32/WinSleep.h>
#endif

namespace Andromeda
{
	namespace Threading
	{
		void Sleep(int miliseconds)
		{
			if (miliseconds >= 0)
			{
				impl::Sleep(miliseconds);
			}
		}

	}
}
