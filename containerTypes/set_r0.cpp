#include <stdio.h>
#include <stdlib.h>

class set
{
	struct node
	{
		int data;
		node *next;
	};
	
	node* first;
	node* last;
	
	public:
	
	set() : first(0), last(0)
	{
		
	};
	
	void add( int value )
	{
		if ( first != 0 )
		{
			node* new_last = new node;
			
			new_last->next = 0;
			new_last->data = value;
			
			last->next = new_last;
			last = new_last;
			
			printf( "other: %i \n", last->data );
		}
		else
		{
			first = new node;
			first->next = 0;
			first->data = value;
			last = first;
			
			printf( "first! %i \n", last->data );
		}		
	};
	
	void count()
	{
		int count = 0;
		node* current = first;
		
		while( current != 0 )
		{
			current = current->next;
			count++;
		};
		
		printf( "count: %i ", count );
	};
	
	void destroy()
	{
		
		node* current = first;
		
		while( current != 0 )
		{
			node* to_delete = current;
			current = current->next;
			delete to_delete;
		};
		
	};
	
	void dump()
	{
		node* current = first;
		
		printf( "<set>\n" );
		
		while( current != 0 )
		{
			node* to_print = current;
			current = current->next;
			printf( " <node>%i</node>\n", to_print->data );
		};
		
		printf( "</set>" );
	};
	
};



 
int  main()
{
    set aset;
    
    aset.add( 1 );
    aset.add( 2 );
    aset.add( 3 );
    aset.add( 4 );
    aset.add( 5 );
    
    aset.dump();
    
    return 0;
}
