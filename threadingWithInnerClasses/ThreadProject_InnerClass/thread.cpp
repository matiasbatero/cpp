#ifndef _Thread_h
    #include "thread.h"
#endif



Thread::Thread( Action* action, DWORD flags, DWORD timeOut )
{
    terminate = false;
    this->timeOut = timeOut;
    this->action = action;

    //WinAPI thread function...

    thread = ::CreateThread( 0, 0, threadFunction, action, flags, &threadId );

    running = ( flags !=  CREATE_SUSPENDED );
    terminate = false;
}

Thread::~Thread(void)
{
    Terminate();
}

void Thread::Start(void)
{

    if( !running)
    {

        ::ResumeThread( thread);
        running = true;
    }
}

void Thread::Stop(void)
{

    if( running )
    {
        ::SuspendThread(thread);
        running = false;
    }
}

void Thread::Exit(void)
{

    if (!terminate)
    {

        //WINAPI Thread funciton
        ::TerminateThread( thread, 0 );
        ::WaitForSingleObject(thread, timeOut );

        running = false;
        terminate = true;

    }
}

bool Thread::IsRunning(void)
{

    return running;
}

bool Thread::Terminate(void)
{

    return terminate;
}

bool Thread::IsAlive(void)
{

    return !terminate;

}















