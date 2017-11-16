#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

template< int block_size >
class set
{
	struct node
	{
		char data[block_size];
		node* next;
	};
	
	node* first;
	node* last;
	
	bool is_empty()
	{
		return ( first == 0 )? true : false;
	};
	
	bool is_last()
	{
		return ( first == last )? true : false;
	};
	
	node* previous()
	{
		node* sentinel = first;
			
		while( !(sentinel->next == last) )
		{
			sentinel = sentinel->next;
		};
		
		return sentinel;	
	};
	
	public:
	
	set() : first(0), last(0)
	{
		
	};
	
	void add( const byte* block )
	{
		if ( first != 0 )
		{
			node* new_last = new node;
			memset( new_last, 0, sizeof(node) );
			
			new_last->next = 0;
			memcpy( &(new_last->data[0]), block, strlen(block) );
			
			last->next = new_last;
			last = new_last;
			
			printf( "%p -> %*.*s \n", last, 0, block_size, &(last->data[0]) );
		}
		else
		{
			first = new node;
			memset( first, 0, sizeof(node) );
			
			first->next = 0;
			memcpy( &(first->data[0]), block, strlen(block) );
			last = first;
			
			printf( "%p -> %*.*s \n", last, 0, block_size, &(last->data[0]) );
		}
			
	};
	
	void remove()
	{
		if( !is_empty() )
		{
			if ( !is_last() )
			{
				node* prev = previous();
				
				prev->next = 0;
				printf("%p! ", last );
				delete( last );
				last = prev;
				printf(" next to remove %p! \n", last );
			}
			else
			{
				delete( first );
				first = last = 0;
			};
		}
	};
	
	int count()
	{
		int count = 0;
		node* current = first;
		
		while( current != 0 )
		{
			current = current->next;
			count++;
		};
		
		return count;
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
		
		printf( "<set lenght=%i >\n", count() );
		
		while( current != 0 )
		{
			node* to_print = current;
			current = current->next;
			printf( " <item>%*.*s</item>\n", 0, block_size, &(to_print->data[0]) );
		};
		
		printf( "</set>" );
	};
	
};

int splitByNullchar(void)
{
    const char *s = "abc\0def\0ghi\0";
    const char *p = s;

    while (*p) {
        puts(p);
        p = strchr(p, '\0');
        p++;
    }
    return 0;
}


 
int  main()
{
    set<12> aset;
    
    aset.add( "abcdeooooooooooooooo" );
    aset.add( "efghi" );
    aset.add( "jklmn" );
    aset.add( "nopqr" );
	aset.remove();
	aset.remove();
	aset.remove();
	aset.remove();
	aset.remove();
	aset.remove();
    aset.dump();

    //example j;
    
    //j.dump();
    
    return 0;
}
