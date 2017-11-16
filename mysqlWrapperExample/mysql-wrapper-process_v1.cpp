#include <iostream>
#include <list>
#include <vector>
#include <dlfcn.h>
#include <sqlite3.h>
#include <mysql/mysql.h>

using namespace std;

class MySQL
{
	private:
	
	MYSQL* mysql;
	MYSQL_RES* mysql_result;
	int nrows;
	int nfields;
	
	struct
	{
		int nrows;
		int nfields;
		
		char** data;
		char** columns;
	} rdata;

	
	public:
	
	MySQL()
	{
		if (!(mysql = mysql_init(0)) )
		{
			fprintf(stderr, "Failed to instantiate database object: Error: %s\n", mysql_error(mysql) );
		};
		 
	}
	
	~MySQL()
	{
		mysql_close( mysql );
	}
	
	void connect( const char* host, const char* user, const char* passwd, 
				 const char* db, unsigned int port, const char* unix_socket, 
				 unsigned long client_flag )
	{
		
		if ( !mysql_real_connect( mysql, host, user, passwd, db, port, unix_socket, client_flag ) )
		{
			fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(mysql) );
		}
		
	};
	
	void select( const char* db)
	{
		 if( mysql_select_db(mysql, db) ) 
		 {
			fprintf(stderr, "Error: %s\n", mysql_error(mysql) );
			
		}
	};
	
	void query( const char* sql )
	{
		if( mysql_query(mysql, sql ))
		{
			fprintf( stderr, "ERROR: %s\n" , mysql_error( mysql) );
		}
	};
	
	void execute()
	{
		mysql_result = mysql_store_result(mysql);
	};
	
	void retrieve()
	{
		
		if ( mysql_result )
		{
			nrows = mysql_num_rows( mysql_result );
			nfields = mysql_num_fields( mysql_result );
				
		   for ( int l = 0; l < nrows; l++ ) 
		   {
		  
				MYSQL_ROW row = mysql_fetch_row(mysql_result);
				
				for ( int k = 0; k < nfields; k++ )
				{
					cout << ((row[k]==NULL) ? "NULL" : row[k]) << ',';
				};
				
				cout << endl;
		   }
		   
		};
		
		mysql_free_result(mysql_result);
		
	};
};


int main()
{
	MySQL mysql;
	mysql.connect( "localhost", "root", "987654", "users_example2", MYSQL_PORT, NULL, 0 );
	mysql.select( "users_example2" );
	
	mysql.query("select o from telephone");
	mysql.execute();
	mysql.retrieve();
	
	
	
	return 0;
};
