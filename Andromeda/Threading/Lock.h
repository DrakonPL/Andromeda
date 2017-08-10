#ifndef Lock_H
#define Lock_H

namespace Andromeda
{
	namespace Threading
	{
		class Mutex;

		class Lock
		{
		public:

			Lock(Mutex& mutex);
			~Lock();

		private:

			Mutex& _mutex;

		};
	}
}

#endif
