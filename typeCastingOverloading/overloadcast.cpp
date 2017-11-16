/*
 * Overload Type Casting Operator Example
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

class Cents
{
private:
    int m_nCents;
public:
    Cents(int nCents=0)
    {
        m_nCents = nCents;
    }
 
    // Overloaded int cast
    operator int() { return m_nCents; }
 
    int GetCents() { return m_nCents; }
    void SetCents(int nCents) { m_nCents = nCents; }
};

class Dollars
{
private:
    int m_nDollars;
public:
    Dollars(int nDollars=0)
    {
        m_nDollars = nDollars;
    }
 
     // Allow us to convert Dollars into Cents
     operator Cents() { return Cents(m_nDollars * 100); }
};

void PrintCents(Cents cCents)
{
    cout << cCents.GetCents() << endl;
}
 
int main()
{
    Dollars money(9);
    PrintCents(money); // cDollars will be cast to a Cents
 
    return 0;
}
