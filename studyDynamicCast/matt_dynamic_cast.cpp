/*
 * DynamicCast Study
 * Based on example code from Nicolás Gonzalez Ferreira
 * 
 * Copyright 2014 Matías Gastón Santiago <matiasbatero.mdq@gmail.com>
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

#include <iostream>
#include <string>


using namespace std;

class IGreeter
{
    public:
        virtual ~IGreeter() {}
        virtual void greet(string message) = 0;
};

class Greeter : public IGreeter
{
	public:
	void greet(string message)
	{
		cout << "Message is: " << message << endl;
	};
};

class Base { virtual void dummy() {} };
class Derived: public Base { int a; };

int main () 
{
  //Declaramos un Greeter
  Greeter* pGreeter = new ( Greeter );
  
  //Probamos.. funciona OK
  pGreeter->greet("Hola 1");
  
  //También se debería verificar que si greet es derivado de IGreeter, que éste pueda ser casteado a la clase base.
  ( (IGreeter*)pGreeter )->greet("Hola 2");
  
  //Supongamos que el objeto es obtenido por una petición a una Lib. y que es obtenido a través de un void*.. se puede simular el efecto así:
  void* test = pGreeter;
  
  //Esta operación no es válida, por supuesto:
  //test->greet("Hola 3");
  
  //Ahora, sí se puede castear:
  ( (IGreeter*)test )->greet("Hola 3");
  
  //Si bien este casteo también es válido, es incorrecto, ya que desde el main no deberíamos conocer la implementación, solo su interfaz.
  ( (Greeter*)test )->greet("Hola 4"); 
  
  //Ahora, probemos el casteo dinámico.
  //Una vez cargada la lib, y llamada la función que nos devuelve un void* apuntando a un greeter real.
  
  //IGreeter* pIGreeter2 = new ( IGreeter ); (OPERACIÓN INVÁLIDA, no está permitida: cannot allocate an object of abstract type)
  Greeter* pGreeter2 = new ( Greeter );
  void* test2 = pGreeter2;
  
  //Esto es válido.. y siempre se verifica. Pero no sirve para nada, para eso castear estáticamente.
  dynamic_cast<void*>( pGreeter2 ); 
  
  //Esto es válido pero redundante.
  dynamic_cast<Greeter*>( pGreeter2 ); 
  
  //Esto es inválido.. porque dynamic_cast solo es válido con tipos polimórficos.. void* no está considerado polimórfico al estilo c++.
  //Interesante detalle.. ¿construir un voidptr polimórfico?..
  //dynamic_cast<IGreeter*>( test2 );
  
  //Esto es válido, verifica si pGreeter conforma la Interfaz IGreeter. Va por este lado..
  dynamic_cast<IGreeter*>(pGreeter2); 
  
  //Entonces.. 
  IGreeter* test3 = dynamic_cast<IGreeter*>(pGreeter2);
  test3->greet("Hola dynamic_cast");
  

  
  return 0;
}
