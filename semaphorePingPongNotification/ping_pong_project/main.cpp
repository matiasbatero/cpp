/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Sistemas Operativos
 *
 * Ping Pong Sample : Synchronization with semaphores
 *
 * Version:  Revision 1.0  (16/9/2015)
 *
 * Autor:    Santiago, Matías Gastón
 *
 * File:	 main.cpp
 *
 */

#include <iostream>
#include <unistd.h>
#include "pthread_wrapper.hpp"

using namespace std;

//ping-pong thread functions
void* ping(void*);
void* pong(void*);

//semaphores
Semaphore pingThreadAccess(1);
Semaphore pongThreadAccess(0);


int main()
{


    Thread pingThread(ping);
    Thread pongThread(pong);

    pingThread.join();
    pingThread.join();


    return 0;
}


void* ping(void* arg)
{
    while(true)
    {
        pingThreadAccess.wait();
        usleep(1000*500);
        cout << "ping" << endl;
        //cout << "ping";
        pongThreadAccess.signal();
    }

    return nullptr;
}

void* pong(void* arg)
{
    while(true)
    {
        pongThreadAccess.wait();
        usleep(1000*500);
        cout << "pong" << endl;
        //cout << "pong";
        pingThreadAccess.signal();
    }

    return nullptr;
}
