#ifndef WinThread_H
#define WinThread_H

#include <Andromeda/Threading/BaseThread.h>
#include <windows.h>

namespace Andromeda
{
	namespace Threading
	{
		class Thread;

		class WinThread : public BaseThread
		{
		public:

			WinThread(Thread* owner);
			~WinThread();

			void Wait();
			void Cancel();

		private:

			static unsigned int __stdcall entryPoint(void* userData);

			HANDLE _thread;
			unsigned int _threadId;
		};
	}
}

#endif
