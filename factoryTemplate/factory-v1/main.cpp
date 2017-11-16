
/*
 * TDA/TDC/Factory design & implementation V 1.00
 * 
 * 29/6/2015
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
 */

#include "IType.hpp"
#include "IFactory.hpp"

//Here in main, you only know about interfaces and factories to create objects.

int main()
{
	IType* test = Factory<IType>::get();
	
	test->methodA();
	test->methodB();
	test->methodC();
	
	return 0;
};
