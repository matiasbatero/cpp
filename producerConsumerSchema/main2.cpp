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


class ProducerConsumer
{
	private:
	
	Queue<int>* buffer;
	Mutex* bufferAccess;
	Semaphore* bufferNotFull;
	Semaphore* bufferNotEmpty;
	Thread* consumer;
	Thread* producer;
	
	int units;
	
	void* produce(void* arg)
	{
	    for(int i = 1; i < units; i++)
	    {
	        bufferNotFull->wait();
	        bufferAccess->block();
			
			if( !buffer->isFull() )
			{
				cout << "Producing item nro:" << i << endl;				
				buffer->add(i);
			};
			
			bufferAccess->unblock();
			bufferNotEmpty->signal();
	
	    }
	    
	    return nullptr;
	}

	void* consume(void* arg)
	{
	    
	    for(int i = 1; i < units; i++)
	    {
	        bufferNotEmpty->wait();
	        bufferAccess->block();
	
	        if(!buffer->isEmpty() )
	        {
				cout << "\t\t\tConsuming item nro:" << buffer->front() << endl;
				buffer->pop();
			};
	
	        bufferAccess->unblock();
	        bufferNotFull->signal();
	
	    }
		
	    return nullptr;
	}
	
	
	public:
	
	ProducerConsumer(int units) : units(units)
	{
		buffer = new Queue<int>(units);
		bufferNotFull = new Semaphore(units);
	    bufferNotEmpty = new Semaphore(0);
	    bufferAccess = new Mutex;
	    consumer = new Thread( consume  );
	    producer = new Thread( produce );
	}
	
	~ProducerConsumer()
	{
		delete buffer;
		delete bufferNotFull;
		delete bufferNotEmpty;
		delete bufferAccess;
		delete consumer;
		delete producer;
	}
	
	void run()
	{
		producer->join();
		consumer->join();
	};
	
	

};



int main()
{
	cout << "::Producer Activity:: \t::Consumer Activity:: \n\n";
    

	return 0;
}
