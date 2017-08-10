#ifndef Timer_H
#define Timer_H

#include <ctime>

namespace Andromeda
{
	namespace System
	{
		class Timer
		{
		private:

			clock_t lastTime;
			float msec;

		public:

			Timer();

			float GetDelta();
		};
	}
}

#endif