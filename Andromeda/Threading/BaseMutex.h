#ifndef BaseMutex_H
#define BaseMutex_H

namespace Andromeda
{
	namespace Threading
	{
		class BaseMutex
		{
		public:

			virtual ~BaseMutex(){}

			virtual void Lock() = 0;
			virtual void Unlock() = 0;
		};
	}
}

#endif
