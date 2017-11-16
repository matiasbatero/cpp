#ifndef _Writer_h
#define _Writer_H

#ifndef _Action_h
    #include "action.h"
#endif // _Action_h

#ifndef _Thread_h
    #include "thread.h"
#endif // _Thread_h

using namespace std;

class Writer : public Thread
{
public:

    Writer(void) : Thread( writerAction = new WriterAction(this) )
    {

    };

    ~Writer(void)
    {
        if ( writerAction ) delete writerAction;
    }

    unsigned long Execute(void)
    {
        while (!Terminate() )
        {

            cout << "Writer working..." << endl;
        };

        return 0;
    }

private:

    class WriterAction : public Action
    {
    public:

        WriterAction( Writer* const writer ) : object(writer)
        {

        };

        ~WriterAction(void)
        {

        };

        unsigned long virtual Execute(void)
        {
            object->Execute();
            return 0;
        };

    private:
        Writer* object;
    };

    WriterAction* writerAction;

};


#endif // _Writer_h
