/**
* 
* Copyright (c) 2016 Santiago Matías Gastón <matiasbatero.mdq@gmail.com. All rights reserved. 
* This file is part of C/C++ Static Framework.
* Not Released with license, only for personal and friends use.
* 
* Title: Implementation for stack-based short static string.
* Details: Stack string have a fixed size of 255 char max, like Pascal short-string.
* 
* Comments: This class doesn't have defined interface yet, at 14/9/2016.
* 
* 
* string.cpp
* 
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

template<unsigned char max_char>
class string
{
	/* Fixed size adjustment */
	#define MAX_CHARS max_char
	
	/* Implementation */
	#define MIN_CHARS 0
	#define MIN_CHAR_POS MIN_CHARS
	#define MAX_CHAR_POS MAX_CHARS-1
	#define NULL_CHAR '\0'
		
	unsigned char size;
	unsigned char rep[MAX_CHARS];
	
	/* memory block assigment functions*/
	void init()
	{
		memset( &rep[MIN_CHAR_POS], NULL_CHAR, MAX_CHARS );		
	};
	
	void clone( const string& from, string& to )
	{
		to.size = from.size;
		memcpy( &to, &from, MAX_CHARS );
	};
	
	/* properties */
	bool is_empty()
	{
		return ( size == 0 )? true : false;
	};
	
	bool have_space() const
	{
		return ( size < MAX_CHAR_POS )? true : false;
	};
	
	bool valid_index( unsigned int idx) const
	{
		return ( idx >= MIN_CHAR_POS && idx <= MAX_CHAR_POS ) ? true : false;
	};
	
	/* index management */
	unsigned int first() const
	{
		return MIN_CHAR_POS;
	};
	
	unsigned int last() const
	{
		return ( size == 0 )? size : size-1;
	};
	
	unsigned int free() const
	{
		return size;
	};
	
	/* char manipulation*/
	char get_char( unsigned int pos ) const
	{
		return ( valid_index(pos) )? rep[pos] : NULL_CHAR;
	}; 
	
	void replace_char( unsigned int pos, unsigned char chr )
	{
		if ( valid_index(pos) && chr != '\0' )
		{
			rep[pos] = chr;
		};
	};
	
	void append_char( unsigned char chr )
	{
		if ( have_space() && chr != '\0' )
		{
			rep[ free() ] = chr;
			
			if ( size <= MAX_CHAR_POS )
				size++;
		};
	};
	
	void remove_last_char()
	{
		if ( !is_empty() )
		{
			rep[last()] = NULL_CHAR;
			size--;
		};
	};
	
	public : string& swap_char( unsigned int index, unsigned int new_index )
	{
		if ( (index != new_index) && valid_index(index) && valid_index(new_index) )
		{
			char chr = get_char( new_index );
			replace_char( new_index, get_char(index) );
			replace_char( index, chr );
		};
		
		return *this;
	};
	
	struct range
	{
		unsigned int from;
		unsigned int to;
		
		range(unsigned int f, unsigned int t ): from(f), to(t)
		{
			unsigned int j = from;
			if ( to <= from ){ from = to; to=j;};
		};
		
		unsigned int lenght() const
		{
			return to-from;
		};
	};
	
	bool is_bigger_than_allowed(int s )
	{
		return ( !(s < MAX_CHARS) )? true : false;
	};
	
	public:
	
	string() : size(MIN_CHARS)
	{
		init();
	};
	
	string( const char* cstring ) : size(MIN_CHARS)
	{
		init();
		int size = strlen( cstring );
	
		if ( !is_bigger_than_allowed(size) )
		{
			for ( int pos = 0; pos < size; pos++ )
				append_char( *(cstring+pos) );
		}
		else
		{
			for ( int pos = 0; pos < MAX_CHAR_POS; pos++ )
				append_char( *(cstring+pos) );
			
		};
	};
	
	string( char chr ) : size(MIN_CHARS)
	{
		init();
		append_char( chr );
	};

	string& operator = (const string& input )
	{
		clone( input, *this );
		
		return *this;		
	};
	
	string& operator = ( const char* cstring )
	{
		init();
		size = MIN_CHARS;
		int size = strlen( cstring );
	
		if ( !is_bigger_than_allowed(size) )
		{
			for ( int pos = 0; pos < size; pos++ )
				append_char( *(cstring+pos) );
		}
		else
		{
			for ( int pos = 0; pos < MAX_CHAR_POS; pos++ )
				append_char( *(cstring+pos) );
			
		};
		
		return *this;		
	};
	
	string& operator = ( char chr )
	{
		init();
		size = MIN_CHARS;
		append_char( chr );
		
		return *this;
	};
	
	string& operator + ( char input )
	{
		append_char( input );

		return *this;
	};
	
	string& operator + ( const string& input )
	{
		int size = input.lenght();
		
		for ( int pos = input.first(); pos <= size; pos++ )
			append_char( input.get_char(pos) );
	
		return *this;
	};
	
	string& operator + ( const char* const cstring )
	{
		int size = strlen( cstring );
	
		for ( int pos = 0; pos < size; pos++ )
			append_char( *(cstring+pos) );
	
		return *this;
	};
	
	unsigned int lenght() const
	{
		return size;
	};
	
	string split( unsigned int pos )
	{
		string result;
		int limit = last();
		
		if ( valid_index(pos) )
		{
			for ( int i = pos; i<=limit; i++ )
				result.append_char( get_char(i) );
			
			for ( int i = pos; i<=limit; i++ )	
				remove_last_char();
		};
		
		return result;
	};
	
	string select( unsigned int from, unsigned int to )
	{
		static string selection;
		
		if ( from >= MIN_CHAR_POS && to <= MAX_CHAR_POS )
		{
			if ( to > from )
			{
				for ( unsigned int pos = from; pos <= to; pos++ )
				{
					selection.append_char( this->get_char(pos) );
				};
			}
			else if ( from > to )
			{
				for ( unsigned int pos = to; pos <= from; pos++ )
				{
					selection.append_char( this->get_char(pos) );
				};
			}
		};
		
		return selection;
	};
	
	string& swap( const range substring_a, const range substring_b )
	{
		if ( substring_a.lenght() == substring_b.lenght() )
		{
			for ( unsigned int i=0; i<=substring_a.lenght(); i++)
				swap_char(substring_a.from + i, substring_b.from + i );
				
		};
		
		return *this;
	};
	
	string& insert( string input, unsigned int pos )
	{
		string part = this->split(pos);
		
		return *this+input+part;				
	};
	
	/* C convertions */
	
	//Warning: const char* conversion is very unsafe, there is no way to
	//allow "c-style-string" access without violating the string const-correctness
	//any function "c-style" can override the size counting, destroy the '\0' convention
	//override the internal representation address and make the pointer pass from stack
	//to heap, for functions that applies 'malloc' 'realloc' internally. 
	//Maybe, this conversion will be removed for integrity.
	
	operator const char*()
	{
		return (const char*)&rep[MIN_CHAR_POS];
	};
		
	operator char()
	{
		return ( !is_empty() )? (char)rep[0] : '\0';
	};
	
	operator unsigned char()
	{
		return ( !is_empty() )? rep[0] : '\0';
	};
	
	operator int()
	{
		return atoi((const char*)&rep[0]);
	};
	
	operator long int()
	{
		return atol((const char*)&rep[0]);
	};
	
	operator unsigned long int()
	{
		return strtoul ((const char*)&rep[0], 0, 0);
	};
	
	operator long long int()
	{
		return atoll((const char*)&rep[0]);
	};
	
	operator unsigned long long int()
	{
		return strtoull ((const char*)&rep[0], 0, 0);
	};
	
	operator float()
	{
		return atof( (const char*)&rep[0] );
	};
	
	operator double()
	{
		return strtod ((const char*)&rep[0], 0);
	};
	
	operator long double()
	{
		return strtold ((const char*)&rep[0], 0);
	};
	
};


#define const_char_510 "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234"
#define const_char_252 "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901"
#define const_char_250 "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
#define const_char_4 "abcd"
#define const_char_1 "K"
#define const_char_0 ""

int main()
{
	/*Testing default initialization*/
	printf("Testing default initialization\n");
	printf("------------------------------\n\n");
	
	string<25> a = "";
	string<25> b = "0123456789";
	string<25> c = "abcdefghijklmnopqrstuvwxyz";
	string<25> d = const_char_250;
	string<25> e = const_char_252;
	string<25> f = const_char_510;
	
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)a, a.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)b, b.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)c, c.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)d, d.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)e, e.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)f, f.lenght() );
	
	/*Testing assigment operation*/
	printf("\nTesting assigment operation\n");
	printf("------------------------------\n\n");
	
	string<25> g = a;
	string<25> h = b;
	string<25> i = c;
	string<25> j = d;
	string<25> k = e;
	string<25> l = f;
	
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)g, g.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)i, i.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)j, j.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)k, k.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)l, l.lenght() );
	
	/*Testing char concatenation operation*/
	printf("\nTesting char concatenation -> CHAR = '*'\n");
	printf("------------------------------------------\n\n");
	
	g+'*';
	h+'*';
	i+'*';
	j+'*';
	k+'*';
	l+'*';
	
	
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)g, g.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)i, i.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)j, j.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)k, k.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)l, l.lenght() );
	
	/*Testing string concatenation operation*/
	printf("\nTesting string concatenation -> STRING = '###'\n");
	printf("------------------------------------------\n\n");
	
	string<25> str = "###";
	
	g+str;
	h+str;
	i+str;
	j+str;
	k+str;
	l+str;
	
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)g, g.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)i, i.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)j, j.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)k, k.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)l, l.lenght() );
	
	/*Testing const char* concatenation operation*/
	printf("\nTesting const char* concatenation -> STRING = '$$$'\n");
	printf("------------------------------------------\n\n");
	
	const char* cstr = "$$$";
	
	g+cstr;
	h+cstr;
	i+cstr;
	j+cstr;
	k+cstr;
	l+cstr;
	
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)g, g.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)i, i.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)j, j.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)k, k.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)l, l.lenght() );
	
	/*Testing split division operation*/
	printf("\nTesting split division operation at pos 5\n");
	printf("------------------------------------------\n\n");
	
	string<25> m = g.split(5);
	string<25> n = h.split(5);
	string<25> o = i.split(5);
	string<25> p = j.split(5);
	string<25> q = k.split(5);
	string<25> r = l.split(5);
	
	printf("1 string value: '%s'\nlenght: %i\n\n", (const char*)g, g.lenght() );
	printf("1 string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	printf("1 string value: '%s'\nlenght: %i\n\n", (const char*)i, i.lenght() );
	printf("1 string value: '%s'\nlenght: %i\n\n", (const char*)j, j.lenght() );
	printf("1 string value: '%s'\nlenght: %i\n\n", (const char*)k, k.lenght() );
	printf("1  string value: '%s'\nlenght: %i\n\n", (const char*)l, l.lenght() );
	
	
	printf("2 string value: '%s'\nlenght: %i\n\n", (const char*)m, m.lenght() );
	printf("2 string value: '%s'\nlenght: %i\n\n", (const char*)n, n.lenght() );
	printf("2 string value: '%s'\nlenght: %i\n\n", (const char*)o, o.lenght() );
	printf("2 string value: '%s'\nlenght: %i\n\n", (const char*)p, p.lenght() );
	printf("2 string value: '%s'\nlenght: %i\n\n", (const char*)q, q.lenght() );
	printf("2 string value: '%s'\nlenght: %i\n\n", (const char*)r, r.lenght() );
	
	/*Testing insertion operation*/
	printf("\nTesting insertion operation -> STRING = '___' at pos 3\n");
	printf("------------------------------------------\n\n");
	
	const char* istr = "___";
	
	g.insert(istr, 3 );
	h.insert(istr, 3 );
	i.insert(istr, 3 );
	j.insert(istr, 3 );
	k.insert(istr, 3 );
	l.insert(istr, 3 );
	
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)g, g.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)i, i.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)j, j.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)k, k.lenght() );
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)l, l.lenght() );
	
	
	/*Testing swap substring operation*/
	printf("\nTesting swap substring (0,1) && (4,5)\n");
	printf("------------------------------------------\n\n");
	
	//g = "0123456789";
	//g.swap_char( 0, 9 );
	h.swap( {0,1}, {7,8} );
	//h.swap( {0,1}, {7,8} );
	//i.swap( {0,1}, {7,8} );
	//j.swap( {0,1}, {7,8} );
	//k.swap( {0,1}, {7,8} );
	//l.swap( {0,1}, {7,8} );
	
	printf("string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	//printf("string value: '%s'\nlenght: %i\n\n", (const char*)h, h.lenght() );
	//printf("string value: '%s'\nlenght: %i\n\n", (const char*)i, i.lenght() );
	//printf("string value: '%s'\nlenght: %i\n\n", (const char*)j, j.lenght() );
	//printf("string value: '%s'\nlenght: %i\n\n", (const char*)k, k.lenght() );
	//printf("string value: '%s'\nlenght: %i\n\n", (const char*)l, l.lenght() );
	
	return 0;
};
