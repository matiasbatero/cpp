#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <iostream>
using std::string;

void to_stdout( const char* input )
{
	while( *input )
	{
		putc( *input, stdout );
		input++;
	};
};

void mv_stdout( const char* input )
{
	fputs( input, stdout );
};

void main_view()
{
	to_stdout( "Content-type:text/html; charset=UTF-8\r\n\r\n\
				<!DOCTYPE html><html><body>\
				<meta http-equiv='Cache-Control' content='no-cache, no-store, must-revalidate'/>\
				<meta http-equiv='Pragma' content='no-cache'/>\
				<meta http-equiv='Expires' content='0'/>");
				
	to_stdout( "<script type='text/javascript' language='javascript'>\
				var params = '';\
				function getStringFromServer()\
		        {\
		            var ajax_url = 'hello_ajax.exe';\
		            ajax_url += '?' + 'function'+'=get_time';\
					var ajax_request = new XMLHttpRequest();\
		            ajax_request.onreadystatechange = function()\
		            {\
		                if (ajax_request.readyState == 4 ) \
		                {\
		                    var response = ajax_request.responseText;\
		                    document.getElementById('text').innerHTML = response;\
		                };\
		            };\
		            ajax_request.open( 'GET', ajax_url, true );\
		            ajax_request.send();\
		        };\
		        </script>");
	
	to_stdout( "<input type=\"button\" value=\"getTimeFromServer\" onClick=\"getStringFromServer();\">\
				<p id='text'></p>" );			
				
	to_stdout( "</body></html>" );
	
};



void process_get_http_request( void(&default_response)(void) )
{
	if( getenv("REQUEST_METHOD") == NULL )
    {
        to_stdout( "The request method is NULL");      
    }
    else
    {
        string request_method = getenv("REQUEST_METHOD");

        if( request_method == "GET")
        {
			string request_string = getenv("QUERY_STRING");
			
			if( request_string == "" )
			{
				default_response();	
			}
			else
			{
				//process query string ( this example must return any string in the view.
				to_stdout( "Content-type:text/plain; charset=UTF-8\r\n\r\n");
				time_t t;
				time(&t);
				printf("server date-time : %s",ctime(&t));			
			};
		}

    }
};

int main(int argc , char** argv )
{
    
    process_get_http_request( main_view );    

    return 0;
}
