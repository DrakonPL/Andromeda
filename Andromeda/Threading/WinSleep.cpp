#include <Andromeda/Threading/Win32/WinSleep.h>
#include <windows.h>

namespace Andromeda
{
	namespace Threading
	{
		namespace impl
		{
			void Sleep(int miliseconds)
			{
				::Sleep(miliseconds);
			}
		}
	}
}
