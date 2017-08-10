#ifndef Thread_H
#define Thread_H

#include <Andromeda/Threading/BaseThread.h>

namespace Andromeda
{
	namespace Threading
	{
		struct ThreadFunc;

		class Thread
		{
		public:

			template <typename F>
			Thread(F function);

			template <typename F, typename A>
			Thread(F function, A argument);

			template <typename C>
			Thread(void(C::*function)(), C* object);

			~Thread();

			void Start();

			void Wait();

			void Cancel();

			void Run();

		private:

			friend class BaseThread;

			BaseThread* _thread;
			ThreadFunc* _entryPoint;
		};

		// Base class for abstract thread functions
		struct ThreadFunc
		{
			virtual ~ThreadFunc() {}
			virtual void Run() = 0;
		};

		// Specialization using a functor (including free functions) with no argument
		template <typename T>
		struct ThreadFunctor : ThreadFunc
		{
			ThreadFunctor(T functor) : m_functor(functor) {}
			virtual void Run() { m_functor(); }
			T m_functor;
		};

		// Specialization using a functor (including free functions) with one argument
		template <typename F, typename A>
		struct ThreadFunctorWithArg : ThreadFunc
		{
			ThreadFunctorWithArg(F function, A arg) : m_function(function), m_arg(arg) {}
			virtual void Run() { m_function(m_arg); }
			F m_function;
			A m_arg;
		};

		// Specialization using a member function
		template <typename C>
		struct ThreadMemberFunc : ThreadFunc
		{
			ThreadMemberFunc(void(C::*function)(), C* object) : m_function(function), m_object(object) {}
			virtual void Run() { (m_object->*m_function)(); }
			void(C::*m_function)();
			C* m_object;
		};

		////////////////////////////////////////////////////////////
		template <typename F>
		Thread::Thread(F functor) :
			_thread(NULL),
			_entryPoint(new ThreadFunctor<F>(functor))
		{
		}


		////////////////////////////////////////////////////////////
		template <typename F, typename A>
		Thread::Thread(F function, A argument) :
			_thread(NULL),
			_entryPoint(new ThreadFunctorWithArg<F, A>(function, argument))
		{
		}


		////////////////////////////////////////////////////////////
		template <typename C>
		Thread::Thread(void(C::*function)(), C* object) :
			_thread(NULL),
			_entryPoint(new ThreadMemberFunc<C>(function, object))
		{
		}
	}
}

#endif
