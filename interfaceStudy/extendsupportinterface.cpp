/* -----------------------------------------------
 * Study of interfaces in C++
 * -----------------------------------------------
 * 
 * Matías Gastón Santiago. 11/8/2015
 * 
 * Licencia: Pagar por leer esto. Cada caracter, comisión $10 + IVA
 * 
 * Inheritance.
 * Extension of interfaces.
 * -> Extend own interface support using inheritance of interfaces/AbstractClasses
 * -> Extend own interface support using implicit conversion/Composition.
 * 
 * Advantages and disadvantages.
 * 
 * Description:
 * 
 * This simple study, shows the following problem:
 * You create a class, that works fine, but then you need to incorpore more functionality
 * to be used in more contexts. For example, you have some class to represent documents, and
 * satisfaces IWritable, IReadable interfaces. Then, you need to extend your class, and supports,
 * IPrintable behaviour.
 * 
 * To simplify the study, here I took a generic own-class with 2 methods, that works fine for 
 * my context, but then, i need to support COM Microsoft, to allow my class to be used into Microsoft
 * Object Model, in other software. And, add supports to another framework around.
 * 
 * COM support, is showed in this example like, like a simplified IUnknown base class interface.
 * AnotherCOM support, is showed in this example, like a simplified IAnotherCOM framework class interface.
 * 
 * 1º Solution, can be performed through Inheritance of Interfaces.
 * 2º Solution, can be performed through Extending interface using implicit conversion + composition.
 *  
 * Note: No factory-pattern is used here, to avoid complexity in this example.
 * 
 * Matías Gastón Santiago. 11/8/2015
 * 
 *  
 */

#include <iostream>

using namespace std;

//Main Interface (User-Defined)

//USED FOR SOLUTION APPROACH 1
class IMyTypeA;

//USED FOR SOLUTION APPROACH 2
class IMyTypeB;

//New Interfaces to be supported by IMyTypeA or IMyTypeB.

class IUnknown
{
	public:
	
	virtual void AddRef() = 0;
	virtual void QueryInterface() = 0;
	virtual void Release() = 0;
	
};

class IAnotherCOM
{
	public:
	
	virtual void AddReference() = 0;
	virtual const char* AskInterface() = 0;
	virtual int Free() = 0;
	
	//virtual int Release() = 0; Don't work with 1º approach, compiler ambiquity.
	
};

//-----------------------------------------------------------------------
// SOLUTION APPROACH 1: Inheritance Extension
//-----------------------------------------------------------------------

//Definition
class IMyTypeA
{
	public:
	
	virtual void MethodA() = 0;
	virtual void MethodB() = 0;
	
	
};

//Extend MyType interface, introducing new type. 
//Using Inheritance of interfaces. Here, i add "support" to COM & AnotherCOM

class IMyTypeAExtended : public IMyTypeA, public IUnknown, public IAnotherCOM {};

//Implementation of my-own interface. Only supports my interface, and nothing More.

class MyTypeA : public IMyTypeA
{
	private:
	
	int* rep;
	
	public:
	
	virtual void MethodA() { std::cout << "MethodA prints number   :\t" << *rep << std::endl; };
	virtual void MethodB() { std::cout << "MethodB prints number++ :\t" << (*rep+1) <<std::endl; };
	
	MyTypeA() : rep(new int) {};
	
	~MyTypeA() { delete rep; };
};

//Simplified Implementation of Extended Type. Refactoring 1.
class MyTypeAExtended : public IMyTypeAExtended
{
	private:
	
	int* rep;
	int refcount;
	
	public:
	
	virtual void MethodA() { std::cout << "MethodA prints number   :\t" << *rep << std::endl; };
	virtual void MethodB() { std::cout << "MethodB prints number++ :\t" << (*rep+1) <<std::endl; };
	
	MyTypeAExtended() : rep(new int) {};
	
	~MyTypeAExtended() { delete rep; };
	
	//COM implementation supported
	virtual void AddRef() { refcount++; std::cout << "COM1: Added Reference to counter..OK. Current: "<< refcount << std::endl;};
	virtual void Release(){ refcount--; std::cout << "COM1: Released Reference to counter..OK. Current: "<< refcount << std::endl;};
	virtual void QueryInterface() { std::cout << "COM1: MyTypeInterface: void MethodA(); void MethodB()" << std::endl;};
	
	//AnotherCOM implementation supported
	virtual void AddReference() { refcount++; std::cout << "COM2: Added Reference to counter..OK. Current: "<< refcount << std::endl;};
	virtual const char* AskInterface()
	{ 	
		std::cout << "COM2: I return interface through const char*" << std::endl; 
		return "COM2: MyTypeInterface: void MethodA(); void MethodB()";
	};
	
	virtual int Free() { refcount--; std::cout << "COM2: I return refcount" << std::endl; return refcount; };
	
};

	 
//-----------------------------------------------------------------------
// SOLUTION APPROACH 2: Implicit Conversion of Interfaces by Composition.
//-----------------------------------------------------------------------

//Definition

class IMyTypeB
{
	public:
	
	virtual void MethodA() = 0;
	virtual void MethodB() = 0;
	
	//In this approach, IMyTypeB is modified to support more interfaces, but don't break compatility or bloat the interface.
	//Because, the following lines, are not behaviour, and they are used implicity by compiler. Or by explicit cast.
	//And not by a method calls. For this, there is not possibility for a colision symbol names.
	
	//Each new interface to support, you need to define a new operator for your own interface, with the known name-interface.
	
	virtual operator IUnknown*() = 0;
	virtual operator IAnotherCOM*() = 0;
	
	//for testing
	virtual operator IMyTypeB*() = 0;
	
};


//Simplified Implementation : Refactoring 1.
class MyTypeB : public IMyTypeB
{
	private:
	
	class _IUnknown : public IUnknown
	{
		//private:
		MyTypeB* xthis; //eXternal this. (Shares container class context) Ex: Unique Reference Counter.
		
		public:
		_IUnknown(MyTypeB* container) : xthis( container ) {}; //Required to access to outside class
	
			
		//COM implementation supported
		virtual void AddRef()
		{ 
			xthis->refcount++;
			std::cout << "COM1: Added Reference to counter..OK. Current: "<< xthis->refcount << std::endl;
		};
		
		virtual void Release()
		{ 
			xthis->refcount--;
			std::cout << "COM1: Released Reference to counter..OK. Current: "<< xthis->refcount << std::endl;
		};
		
		virtual void QueryInterface() 
		{ 
			std::cout << "COM1: MyTypeInterface: void MethodA(); void MethodB()" << std::endl;
		};
	
	};
	
	class _IAnotherCOM : public IAnotherCOM
	{
		//IAnotherCOM implementation supported
		private:
		MyTypeB* xthis; //eXternal this. (Shares container class context) Ex: Unique Reference Counter.
		
		public:
		_IAnotherCOM(MyTypeB* container) : xthis( container ) {}; //Required to access to outside class
		
		virtual void AddReference()
		{ 
			xthis->refcount++;
			std::cout << "COM2: Added Reference to counter..OK. Current: "<< xthis->refcount << std::endl;
		};
		
		virtual const char* AskInterface()
		{ 	
			std::cout << "COM2: I return interface through const char*" << std::endl; 
			return "COM2: MyTypeInterface: void MethodA(); void MethodB()";
		};
	
		virtual int Free() 
		{
			xthis->refcount--;
			std::cout << "COM2: I return refcount" << xthis->refcount << std::endl; return 0; 
		};
		
	};
	
	_IUnknown* iunknown;
	_IAnotherCOM* anothercom;
	
	
	int rep;
	int refcount;
	
	
	public:
	
	virtual void MethodA() { std::cout << "MethodA prints number   :\t" << rep << std::endl; };
	virtual void MethodB() { std::cout << "MethodB prints number++ :\t" << (rep+1) <<std::endl; };
	
	MyTypeB() : iunknown( new _IUnknown(this) ), anothercom( new _IAnotherCOM(this) ), rep( 9 ), refcount( 0 )
	{};
		

	//Supported interfaces implementation
	virtual operator IUnknown*() { return (IUnknown*)iunknown; };
	virtual operator IAnotherCOM*() { return (IAnotherCOM*)anothercom; };
	
	//for testing
	virtual operator IMyTypeB*() { return this; };
	
};

int function( IUnknown* ptr)
{
	ptr->AddRef();
	return 100;
};

int main()
{
	//-----------------------------------------------------------------------
	// SOLUTION APPROACH 1: Inheritance Extension
	//-----------------------------------------------------------------------
	
	//MyType object (plain)
	cout << "Plain Class\n";
	
	IMyTypeA* test1 = new MyTypeA;
	
	test1->MethodA();
	test1->MethodB();
	
	
	
	// Study Case 1: Supported COM using inheritance.
	// :: IMyTypeCOM, inherits from 2 interfaces: IMyType, IUnknown.
	 
	cout << "\n\nStudy Case 1: Supported COM using Inheritance\n\n";
	 
	IMyTypeAExtended* test2 = new MyTypeAExtended;
	
	// Abstract classes have some degree of polymorphism. It's limited to be verified the
	// range of polymorphic-support at compile time only. So you can be polimorphic, only if you 
	// provide all the possibilities at compile time. 
	// For this, cast's to other interfaces are secure, because symbols are know, due a is-a inheritance
	// relationship, and with the help of an additional indirection level through a virtual table.
	
	// a) IMyTypeCOM can be used as (MyType*) using cast, because is secure. 
	
	cout << "\na) IMyTypeCOM used as IMyType throung secure cast:\n";
	IMyTypeA* test2_a = (IMyTypeA*)test2;
	
	test2_a->MethodA();
	test2_a->MethodB();
	 
	// b) MyTypeCOM can be used as (IUnknown*) using cast, because is secure.
	
	cout << "\nb) IMyTypeCOM used as IUnknown throung secure cast:\n";
	IUnknown* test2_b = (IUnknown*)test2;
	
	test2_b->AddRef();
	test2_b->Release();
	test2_b->QueryInterface();
	
	// c) MyTypeCOM exposes more accesible methods that doesn't introduce more behaviour. Bloated interface.
	
	/* In this case, IUnknown is the new interface to support, but, maybe you need to include support
	 * to another interface. Looks IAnotherCOM, it have 2 methods with the same semantic:
	 * 
	 * AddRef (From IUnknown)  &  AddReference ( From IAnotherCOM).
	 * 
	 * On the client side,  object.AddRef(), and object.AddReference()  are the same.. 
	 * 
	 * For the other side, QueryInterface (From IUnknown) & AskInterface ( From IAnotherCOM), have the same semantic
	 * But, it works different. AskInterface, returns the result, while QueryInterface not.
	 * 		
	 * On the client side, object.AskInterface(), and object.QueryInterface(), have the same meaning, but works 
	 * different, and this approach, introduce the possibility to mix methods, and could be very confusing.
	 * 
	 * The programmer have the responsability of using methods according your context.
	 * Example:  Using Class in a COM Context... only (AddRef, Release, QueryInterface).
	 */
	
	cout << "\nc) While MyTypeCOM grows, semantic can be more confusing. Bloated interface:\n";
	
	test2->MethodA();
	test2->MethodB();
	test2->AddRef();
	test2->AddReference();  //AddRef & AddReference, with equal semantic.
	test2->Release();
	test2->Free();			//Free & Release, with equal semantic, but works different. Allows possibility to mix.
	test2->QueryInterface();
	test2->AskInterface();
	
	
	/* d) MyTypeCOM is "polymorphic by interface", but by brutal force.
	 * 
	 * e) Adding support for many other types of interfaces, introduce more and more complexity, 
	 *    and interface grows in semantic ambiguity. 
	 * 
	 * f) If You want to support different interfaces, that have methods with the same name.
	 *    Compilation cannot be performed because symbol ambiquity. So needs a lot of work.
	 *      -> ( You can, edit MyType and add IUnknown, and work with a big 
	 */
	 
	/* ADVANTAGES of Using Inheritance of Interfaces here.
	 * 
	 * 1) Rapid extension, and direct implementation.
	 * 2) If new interfaces are very little, or conceptually lightweight, can be more suitable. 
	 * 3) Little, compact, lightweight new interfaces are best.
	 * 
	 * DISADVANTAGES of Using Inheritance of Interfaces here.
	 * 
	 * 1) It's not scalable solution. More than 2 interfaces, could be chaotic.
	 * 2) Depending of the interface volume, there are possibility to have symbol-colision names. Solve this, is tedious.
	 * 3) Interface is bloated.
	 * 4) If you want to support at least ~ "2 little interface structures".
	 * 5) If your class, by design cannot be adaptable to support interfaces, you need to edit some part of your own interface
	 *    with possibility to broke or propagate API/ABI compatibility with other parts of the system. (Valid for any approach)
	 * 6) If your class, satisfy the (5º point), and you don't want to redesign your own interface. In some cases, the 
	 *    interface that you want to extend, cannot be implemented to reach the support of the 100%, nut could be functional
	 *    at some level. In this cases, the support of new interfaces is partial. But you pay, with a range of Segregation
	 *    of interfaces, some little segregation, to very high, depending the volume/complexity of the interface that you want 
	 *    to support.
	 * 
	 */    
	 
	//-----------------------------------------------------------------------
	// SOLUTION APPROACH 2: Implicit Conversion of Interfaces by Composition.
	//-----------------------------------------------------------------------
	
	cout << "\n\nStudy Case 2: Supported COM using Implicit conversion by composition \n\n";
	
	
	// a) Instantiation of a class, can admit multiple supported interfaces.
	
	// Create object using IMyType interface (default)
	IMyTypeB* example1 = new MyTypeB;
	

	// Create object using IUnknown interface:
	IUnknown* example2 = (IUnknown*)(*new MyTypeB);
	
	
	// Create object using IAnotherCOM interface:
	IAnotherCOM* example3 = (IAnotherCOM*)(*new MyTypeB);
	
	
	// a) Hidden information is preserved from other interfaces
	
	cout << "IMyTypeB Interface :\n\n";
	example1->MethodA();  //OK
	example1->MethodB();  //OK
	
	//example->AddRef();  //Fail
	//example->AskInterface(); //Fail
	
	cout << "\n\nIUnknown Interface: \n\n";
	example2->AddRef();
	example2->Release();
	example2->QueryInterface();
	
	cout << "\n\nIAnotherCOM Interface: \n\n";
	example3->AddReference();
	example3->Free();
	example3->AskInterface();
	
	
	// b) Cast are secure to other interfaces
	
	cout << "\n\nTesting cast \n\n";
	
	((IMyTypeB*)*example1)->MethodA();
	((IUnknown*)*example1)->AddRef();
	((IAnotherCOM*)*example1)->AddReference();
	
	function( *example1 );
	
	// ADVANTAGES of using Implicit conversion by Composition
	/* a) Extending a interfaces, requires only add a one line of operator at the main own-user defined interface.
	 * 	  This line, doesn't bloat or introduce semantic ambiquity, because, is not behaviour added. Only convertions.
	 * 
	 * b) You have only one component, that supports multiple interfaces, without using inheritance.
	 * 
	 * c) Segregation of interfaces is NULL
	 * 
	 * d) Add support to interfaces, translates in a implementation detail of your class.
	 * 
	 * e) Scalable.
	 * 
	 * DISADVANTAGES:
	 * 
	 * a) Extra level of indirection
	 * 
	 * 
	 * 
	 * 
	*/
	
	return 0;
};
