#ifndef _Thread_h
#define _Thread_h

#ifndef _Action_h
    #include "action.h"
#endif // _Action_h

#include <windows.h>

class Thread
{
    enum { TIME_OUT = 200 };

private:

    HANDLE thread;
    DWORD threadId;
    DWORD timeOut;
    BOOL terminate;
    BOOL running;
    Action* action;

    static unsigned long threadFunction( void* threadAction )
    {
        return ( (Action*) threadAction )->Execute();
    }

public:

    Thread( Action* action, DWORD flags = CREATE_SUSPENDED, DWORD timeOut = TIME_OUT );

    ~Thread(void);

    void Start(void);

    void Stop(void);

    void Exit(void);

    bool IsRunning(void);

    bool Terminate(void);

    bool IsAlive(void);

};

#endif // _Thread_h
