#include <Andromeda/Threading/Win32/WinThread.h>
#include <Andromeda/Threading/Thread.h>
#include <cassert>
#include <process.h>

namespace Andromeda
{
	namespace Threading
	{

		WinThread::WinThread(Thread* owner)
		{
			_thread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &WinThread::entryPoint, owner, 0, &_threadId));
		}

		WinThread::~WinThread()
		{
			if (_thread)
				CloseHandle(_thread);
		}

		void WinThread::Wait()
		{
			if (_thread)
			{
				WaitForSingleObject(_thread, INFINITE);
			}
		}

		void WinThread::Cancel()
		{
			if (_thread)
				TerminateThread(_thread, 0);
		}

		unsigned int __stdcall WinThread::entryPoint(void* userData)
		{
			// The Thread instance is stored in the user data
			Thread* owner = static_cast<Thread*>(userData);

			// Forward to the owner
			owner->Run();

			// Optional, but it is cleaner
			_endthreadex(0);

			return 0;
		}
	}
}