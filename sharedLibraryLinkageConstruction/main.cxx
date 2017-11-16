#include <iostream>
#include "core.hxx"


extern "C"
{

ClassHandler type();


ClassHandler get()
{
	return type();
};

}

int main(int argc, char **argv)
{
	
	
	return 0;
}

