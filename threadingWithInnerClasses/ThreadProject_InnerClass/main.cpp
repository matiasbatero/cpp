#include <iostream>
#include <conio.h>
#include <windows.h>

#ifndef _Writer_h
    #include "writer.h"
#endif // _Writer_h

using namespace std;

int main()
{
    Writer writer;
    writer.Start();
    getch();
    writer.Stop();
    writer.Start();

    for ( int i = 0; i<5000;i++)
    {
        cout << "\t\tMain working..." << endl;

    };

    writer.Stop();
    writer.Exit();
    getch();


    return 0;
}
