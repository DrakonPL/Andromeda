#ifndef BaseThread_H
#define BaseThread_H

namespace Andromeda
{
	namespace Threading
	{
		class BaseThread
		{
		public:

			virtual void Wait() = 0;
			virtual void Cancel() = 0;
		};
	}
}

#endif
