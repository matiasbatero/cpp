/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Sistemas Operativos
 *
 * pthread.h wrapper
 *
 * Version:  Revision 1.0  (15/9/2015)
 *
 * Autor:    Santiago, Matías Gastón
 *
 * File:	 pthread_wrapper.hpp
 *
 */

#ifndef PTHREAD_WRAPPER
#define PTHREAD_WRAPPER

#include <pthread.h>
#include <semaphore.h>

class Thread
{
    private:

    pthread_t thread;
    typedef void* (funcTh)(void*);

    public:

    Thread( void*(thread_function)(void*) )
    {
        pthread_create( &thread, 0, thread_function, 0);
    };

    void join()
    {
        pthread_join(thread, 0);
    }

};

class Mutex
{
    private:

    pthread_mutex_t mtx;

    public:
    Mutex()
    {
        pthread_mutex_init( &mtx, 0 );
    };

    void block()
    {
        pthread_mutex_lock(&mtx);

    };

    void unblock()
    {
        pthread_mutex_unlock(&mtx);
    };

};

class Semaphore
{
    private:

    sem_t sem;

    public:
    Semaphore(int init)
    {
        sem_init(&sem, 0, init);
    };

    void wait()
    {
        sem_wait(&sem);
    };

    void signal()
    {
        sem_post(&sem);
    };

};

#endif // PTHREAD_WRAPPER
