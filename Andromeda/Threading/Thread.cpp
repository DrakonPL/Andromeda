#include <Andromeda/Threading/Thread.h>

#ifdef ANDROMEDA_PC
#include <Andromeda/Threading/Win32/WinThread.h>
#endif

namespace Andromeda
{
	namespace Threading
	{
		Thread::~Thread()
		{
			Wait();
			delete _thread;
		}

		void Thread::Start()
		{
			Wait();
			_thread = new WinThread(this);
		}

		void Thread::Wait()
		{
			if (_thread)
			{
				_thread->Wait();
				delete _thread;
				_thread = NULL;
			}
		}

		void Thread::Cancel()
		{
			if (_thread)
			{
				_thread->Cancel();
				delete _thread;
				_thread = NULL;
			}
		}

		void Thread::Run()
		{
			_entryPoint->Run();
		}

	}
}
