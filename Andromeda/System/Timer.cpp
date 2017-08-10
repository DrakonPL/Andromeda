#include <Andromeda/System/Timer.h>
#include <time.h>

namespace Andromeda
{
	namespace System
	{
		Timer::Timer()
		{
			lastTime = clock();
		}

		float Timer::GetDelta()
		{
			clock_t now = clock();
			clock_t delta = now - lastTime;
			lastTime = now;

			msec = ((float)delta) / CLOCKS_PER_SEC;

			return msec;
		}
	}
}
