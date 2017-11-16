/*
 * Source/Target Class Prototype Experiment
 * Comunicación entre clases autónomas a través de un canal
 * Matías G. Santiago (2015)
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



class Source
{
	private:
	const char* data;


	public:

	Source()
	{
		data = "NULL SND";

	};

	void Load( const char* sms )
	{
		data = sms;
	};

	const char* Get()
	{
		return data;
	};

};

class Target
{
	private:
	const char* data;

	public:

	Target()
	{
		data = "NULL RECV";
	};

	void Show()
	{
		std::cout << data << std::endl;
	};

	void Get( const char* sms )
	{
		data = sms;
	};


};


/* Aca viene el asunto. A pesar de ser una pedorrada que lo haga con referencias,
 * solo esta hecho con motivo de ver que pasa si se las usa.*/

class Channel
{
	private:

	Source& src;
	Target& trg;


	public:

    Channel( Source& source, Target& target ):
        src (source)
          ,trg(target)
    {

    };

    void Transmit()
    {
        trg.Get( src.Get() );
    };
};




int main()
{
	Source me;
	Target myfriend;



	Channel channel( me, myfriend );

	me.Load(" Hello my friend...");

	channel.Transmit();

	myfriend.Show();





	return 0;
}
