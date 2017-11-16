/*
 * Pruebas que determinan que el puntero puede moverse más allá de los limites
 * del bloque de memoria de una instancia.
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

#include <iostream>

using namespace std;

int main()
{
    //variable estática
    int A = 100;

    //puntero inicializado en A
    int* pointToA = &A;

    cout << *pointToA << endl;


    //epa... y esto funciona? sí.. comportamiento anómalo.
    cout << *(pointToA + 1 ) << endl;

    // +2 ?
    cout << *(pointToA + 2 ) << endl;

    // +3 ?
    cout << *(pointToA + 3 ) << endl;


    // hasta donde? 500?

    for (int i=0; i<=500; i++)
    {
        cout << *(pointToA + i) << endl;
    }

    // más!! 4500!! (ahora si salta el segmentation fault)

    for (int i=0; i<=4500; i++)
    {
        cout << *(pointToA + i) << "Desplazamiento del puntero i : " << i << endl;
    }

    //detectado.. segmentation fault a i = ??? es variable!! ejecutá varias veces!


    return 0;
}
