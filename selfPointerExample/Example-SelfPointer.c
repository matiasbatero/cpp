/*
 * Pointers Example.
 * 
 * Copyright 2015 Matías Gastón Santiago <matiasbatero.mdq@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>

//Explicit declaration of <type> (In C++ is not necessary, is implicit!)
typedef struct Vehicle Vehicle;

struct Vehicle
{
	//"This" pointer (In C++ this pointer is implicit, but not in C! so, we can implement it. Wait there is necessary here? Look all the code!)
	Vehicle* this;
	
	//Pointer to functions! (In C++ are methods, but in C is not allowed)
	void (*Init)( Vehicle* vehicle );
	
	void (*PowerOn)( Vehicle* );
	Vehicle* (*AddFuel)( Vehicle*, int );
	
	/* Why I put "Vehicle*" as parameters on that functions?. Because, in C i don't have own methods like C++, i have pointer to functions.
	 * The functions are outside of the context of this struct. That means, that the function never see the internal structure of
	 * this struct, so it cannot handle the internal members. We need to pass some "extra" information, so that it can meet its scope.
	 * The "extra information" is a pointer to the Vehicle structure. In C++, that information is passed implicitly! But not here. */
	 
	
	//Attributes
	int m_fuel;
};


Vehicle* AddFuel( Vehicle* vehicle, int fuel )
{
	//Now, through Vehicle* we can access to m_fuel attribute member!
	vehicle->m_fuel = fuel;
	
	//Return what? ( Two ways.. using our "this", but.. we need really here? is the same value of vehicle parameter! )
	return vehicle->this;
	
	//This works of course! but we need one return, not two!. So comment what you want.
	//return vehicle;
}

void PowerOn( Vehicle* vehicle )
{
	//The same!
	( vehicle->m_fuel > 0 )? printf( "Power on!\n" ) : printf( "I need fuel to work! :(\n" );
}

void Init( Vehicle* vehicle )
{
	//The same, but this is important. Here in C, we don't have a lenguage mechanism to initialize something like a constructor.
	//So we need to build, "something similar".
	vehicle->this = vehicle;
	
	vehicle->m_fuel = 0;
	
}


int main( void )
{
	
	//Instance of Vehicle (Static)
	Vehicle  car;
		
	//We need to connect the pointers with the external functions!
	car.Init = &Init;
	car.PowerOn = &PowerOn;
	car.AddFuel = &AddFuel;
	
	//Initialization of car (We need to provide the extra information! AddressOf(Car) )
	car.Init( &car );
	
	car.PowerOn( &car );  //OUTPUT : I need fuel to work! (Yes, Init() put Fuel = 0)!
	
	
	//Look that AddFuel() return "this" or vehicle* .. that is equal to &car
	car.AddFuel( &car, 70 )->PowerOn( &car ); //OUTPUT : Power On!
	
	
	/*Conclusions: We need to observe that, yes, it works.. but is more irritating to read. Because we need to pass explicit information, that isn't important
	 * for us, but it is very important for the compiler to solve the context. Also, look that we use "car." (a dot) but.. in the rest, "->".. 
	 * So there is another trouble, because the notation is not uniform. We can fix that, using a Vehicle* car = &car0.. and fix all the &car references.
	 * 
	 * The best can we can here is:
	 * 
	 * car->AddFuel( &ref, 70 )->PowerOn( &ref )
	 * 
	 * and this results better, because always we use "->" notation.
	 * 
	 * 
	 * C++ simplifies more! because we can avoid set pointers to functions, Init(), etc.. and we can write:
	 * 
	 * car->AddFuel(70)->PowerOn();
	 * 
	 */
	
	
	
	return 0;
}

