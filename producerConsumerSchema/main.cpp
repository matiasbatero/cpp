/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Sistemas Operativos
 *
 * Producer/Consumer sample
 *
 * Version:  Revision 1.0  (16/9/2015)
 *
 * Autor:    Santiago, Matías Gastón
 *
 * File:	 main.cpp (test file)
 *
 */

#include <iostream>
#include <unistd.h>
#include "./types/container/QueueCircular.hpp"
#include "./types/sync/pthread_wrapper.hpp"

using namespace std;

const int TOTAL_ITEMS = 50;

template <typename Type>
class Buffer : public IQueue<Type>
{
    private:

    Queue<Type>* buffer;

    public:

    Buffer(int nitems)
    {
        buffer = new Queue<Type>(nitems);
        bufferNotFull = new Semaphore(nitems);
        bufferNotEmpty = new Semaphore(0);
        bufferAccess = new Mutex;

    }

    ~Buffer()
    {
        delete bufferAccess;
        delete bufferNotEmpty;
        delete bufferNotFull;
    }

    virtual void add( const Type& item )
    {
        buffer->add(item);

    }

	virtual bool isEmpty()
	{
	    return buffer->isEmpty();
	}

	virtual bool isFull()
	{
	    return buffer->isFull();
	}

	virtual Type& front()
	{
	    return buffer->front();
	}

	virtual const Type& front() const
	{
	    return buffer->front();
	}

	virtual void pop()
	{
	    buffer->pop();
	}

    //this is not correct, only for testing.
	Mutex* bufferAccess;
    Semaphore* bufferNotFull;
    Semaphore* bufferNotEmpty;

};

Buffer<int> buffer(3);
void* produceItem(void*);
void* consumeItem(void*);

int main()
{
	cout << "::Producer Activity:: \t::Consumer Activity:: \n\n";

    Thread producer( produceItem );
    Thread consumer( consumeItem );

    producer.join();
    consumer.join();

	return 0;
}


void* produceItem(void* arg)
{
    for(int i = 1; i <= TOTAL_ITEMS; i++)
    {
        buffer.bufferNotFull->wait();
        buffer.bufferAccess->block();

		if( !buffer.isFull() )
		{
			cout << "Producing item nro:" << i << endl;
			buffer.add(i);
			usleep(1000*2);
		};

		buffer.bufferAccess->unblock();
		buffer.bufferNotEmpty->signal();

    }

    return nullptr;
}

void* consumeItem(void* arg)
{

    for(int i = 1; i <= TOTAL_ITEMS; i++)
    {
        buffer.bufferNotEmpty->wait();
        buffer.bufferAccess->block();

        if(!buffer.isEmpty() )
        {
			cout << "\t\t\tConsuming item nro:" << buffer.front() << endl;
			buffer.pop();
			usleep(1000*5);
		};

        buffer.bufferAccess->unblock();
        buffer.bufferNotFull->signal();

    }

    return nullptr;
}
