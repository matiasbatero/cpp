#include <stdio.h>
#include <stdlib.h>


struct list
{
	struct data_node
	{
		char data[8];
		data_node* prev;
		data_node* next;
	};
	
	data_node* current = 0;
	data_node* prev = 0;
	
	public:
	
	void push( char value[8], int size )
	{
		prev = current;
		
		data_node* new_data_node = new data_node;
		current = new_data_node;
		
		current->next = 0;
		current->prev = prev;
	};
	

};

int main()
{
   
   return 0;
}
