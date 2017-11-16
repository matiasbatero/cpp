/* 
 * Trabajo práctico EDI 3 : Modelo de Estados p/Microondas
 * Alumno: Matías Gastón Santiago
 * Fecha: 3/6/2016
 * 
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <mutex>

using namespace std;

class IAction
{
	public:
	
	virtual void execute() = 0;
};

template<typename T>
class Action : public IAction
{
	typedef void(T::* function )(void);

	T* object;
	function func;
	
	public:
	
	Action( T* who, function what ) : object(who), func(what)
	{
				
	};
	
	virtual void execute()
	{
		( object->*func )();
	};
	
	virtual ~Action()
	{
		object = nullptr;
	};
};

class Door
{
	bool _open;
	
	public:
	
	Door():_open(false){};
	
	void open(){ _open = true; cout << "door is open" << endl; };
	void close(){ _open = false; cout << "door is closed" << endl;  };
	bool isOpen(){ return _open; };
};

class Lamp
{
	bool _on;
	
	public:
	
	Lamp():_on(false){};
	
	void on(){ _on = true; cout << "lamp is on" << endl; };
	void off(){ _on = false; cout << "lamp is off" << endl; };
	bool isOn(){ return _on; };
};


class Thread
{
	private:
	
	typedef void*(*tfunction)(void*);
	
	tfunction _function;
	void* _arg;
	pthread_t id;
	pthread_mutex_t count_mutex;
	bool _isRunning;
	
	public:
	
	Thread( tfunction threadFunction, void* arg )
	: _function( threadFunction ), _arg(arg),count_mutex(PTHREAD_MUTEX_INITIALIZER),
	  _isRunning(false)
	{
		pthread_mutex_init( &count_mutex, 0 );
	};
	
	void start()
	{
		pthread_mutex_lock( &count_mutex );
		if ( pthread_create( &id, NULL, _function, _arg ) && !_isRunning )
		{
			_isRunning = true;
		};
		pthread_mutex_unlock( &count_mutex );	
	};
	
	void stop()
	{
		if ( _isRunning )
		{
			pthread_mutex_lock( &count_mutex );
			pthread_cancel(id);
			_isRunning = false;
			pthread_mutex_unlock( &count_mutex );
		}
	}
			
	bool isRunning()
	{
		return _isRunning;
	};
	
	void restart()
	{
		this->stop();
		this->start();
	};

	void wait( const Thread& thread )
	{
		pthread_mutex_lock( &count_mutex );
		pthread_join( thread.id, nullptr );
		pthread_mutex_unlock( &count_mutex );		
	}
	
	~Thread()
	{
		pthread_mutex_destroy(&count_mutex);
		pthread_cancel(id);
	};
};








class Timer
{
	private:
	
	struct TimerData
	{
		int time;
		int* current;
		IAction* action;
	};
	
	Thread* timer;
	TimerData data;
	
	
	static void* simpleTimer (void* unused)
	{
		pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_init( &count_mutex, 0);

		TimerData& data = *((TimerData*)unused);
		
		
		int currentTime = data.time;
		int firstTime = data.time;
		int runningTime = firstTime;
	
		while( runningTime > 0 )
		{
			pthread_mutex_lock( &count_mutex );
			
			cout << runningTime << endl;
			runningTime--;
			data.current = &runningTime;
			
			if( firstTime != data.time )
			{
				currentTime = data.time;
				firstTime = data.time;
				runningTime = firstTime;
			};
			
			pthread_mutex_unlock( &count_mutex );
			
			sleep(1);
		};
		
		if ( data.action )
			data.action->execute();
		
		pthread_mutex_destroy(&count_mutex);

		return NULL;
	};
	
	Timer( const Timer& ){};
	
	public:
	
	
		
	void start()
	{
		timer->start();
		cout << "timer starts to run..." << endl;
	};
	
	void stop()
	{
		timer->stop();
		cout << "timer is stopped" << endl;
		
	};
	
	int getCurrentTime()
	{
		return *(data.current);
	};
	
	void setTime( int sec )
	{
		data.time = sec;
	};
	
	Timer( IAction* onExpiration )
	{
		data.time = 0;
		data.current = 0;
		data.action = onExpiration;
		
		timer = new Thread( &simpleTimer, &data );
	};
	
	~Timer()
	{
		this->stop();		
		delete timer;
	};
};



class Button
{
	public:
	
	void push(){ cout << "button pushed" << endl; };
};

class Magnetron
{
	bool _on;
	
	public:
	
	Magnetron():_on(false){};
	
	void on(){ _on = true; cout << "magnetron is on" << endl; };
	void off(){ _on = false; cout << "magnetron is off" << endl;};
	bool isOn(){ return _on; };
};

class Speaker
{
	public:
	
	void play(){ cout << "playing sound from speaker" << endl; };
};




















class Oven
{
	
	typedef void(Oven::* state)(void);
	typedef void(Oven::* event)(void);

	Door* door;
	Timer* timer;
	Lamp* lamp;
	Button* button;
	Magnetron* magnetron;
	Speaker* speaker;
	
	state current;
	
	//states
	void Idle();
	void Cooking();
	
	//state activities
	void IdleActivity();
	void CookingActivity();
	
	//state setters
	void setIdle();
	void setCooking();
	
	Action<Oven>* timerExpirationAction;
	
	template<event>
	void processEvent();
	
	void onOvenTimerExpiration();
	
	public:
	
	Oven();
	
	void open();
	
	void close();
	
	void push();
	
	bool isIdle();
	
	bool isCooking();
	
	~Oven();
	
};

Oven::Oven()
{
	timerExpirationAction = new Action<Oven>( this, &Oven::onOvenTimerExpiration );
	timer = new Timer( timerExpirationAction );
	door = new Door;
	lamp = new Lamp;
	magnetron = new Magnetron;
	speaker = new Speaker;
	button = new Button;
	
};

Oven::~Oven()
{
	delete timer;
	delete door;
	delete lamp;
	delete magnetron;
	delete speaker;
	delete button;
	delete timerExpirationAction;
};

//states
void Oven::Idle()
{ 
	IdleActivity(); 
};

void Oven::Cooking()
{
	CookingActivity();
};

void Oven::IdleActivity()
{
};

void Oven::CookingActivity()
{
};

void Oven::setIdle()
{ 
	magnetron->off();
	current = &Oven::Idle;
	(this->*current)();
};

void Oven::setCooking()
{
	magnetron->on();
	current = &Oven::Cooking;
	(this->*current)();
};

template<>
void Oven::processEvent<&Oven::open>()
{
	if ( isCooking()  )
	{
		setIdle();
		
		{ 
			lamp->off(); 
			timer->stop();
		};
	};	
};	

template<>
void Oven::processEvent<&Oven::close>()
{
};	

template<>
void Oven::processEvent<&Oven::push>()
{
	if ( !isCooking() && !door->isOpen() )
	{
		setCooking();
		
		{
			lamp->on(); 
			timer->setTime(60);
			timer->start();
		};
	};
	
	if ( isCooking() )
	{
		{
			timer->setTime( timer->getCurrentTime() + 60 );		
		};
	};
};


template<>
void Oven::processEvent<&Oven::onOvenTimerExpiration>()
{
	if ( isCooking() )
	{
		setIdle();
		
		{
			timer->setTime(0);
			lamp->on();
			speaker->play();
		};
	};
};

void Oven::onOvenTimerExpiration()
{
	processEvent< &Oven::onOvenTimerExpiration >();
};

void Oven::open()
{
	door->open();
	processEvent< &Oven::open >();
};

void Oven::close()
{
	door->close();
	processEvent< &Oven::close >();		
};

void Oven::push()
{
	button->push();
	processEvent< &Oven::push >();
};

bool Oven::isIdle()
{ 
	return ( current == &Oven::Idle )? true : false; 
};

bool Oven::isCooking()
{ 
	return ( current == &Oven::Cooking )? true : false; 
};



int main()
{
	Oven* aOven = new Oven;
	
	aOven->open();
	aOven->close();
	aOven->push();
	
	delete aOven;

	return 0;
};
