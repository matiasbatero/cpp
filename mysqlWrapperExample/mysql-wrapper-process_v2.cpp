#include <iostream>
#include <list>
#include <vector>
#include <dlfcn.h>
#include <string.h>
#include <mysql/mysql.h>

using namespace std;

class number
{
	private:
	
	long double a;
	
	public:
	
	number( long double digit ){};
	
};

class in
{
	public:
	
	virtual const in& operator << ( const char* stream )
	{
		return *this;
	}
};

void showInfoForColumn( MYSQL_FIELD* field, int n )
{
	cout << endl << endl << "COLUMN " << n << endl;
	cout << "column name (cstring): " << field->name << endl;
	cout << "column name without alias: " << field->org_name << endl;
	cout << "table name: " << field->table << endl;
	cout << "table name without alias: " << field->org_table << endl;
	cout << "database name: " << field->db << endl;
	cout << "string size of column name: " << field->length << endl;
	cout << "maximum width of the field for the result set (string representation): " << field->max_length << endl;
	cout << "type of the column: " << field->type << endl;
};

class MySQL
{
	private:
	
	MYSQL* mysql;
	MYSQL_STMT* stmt;
	MYSQL_BIND* bind_in;
	MYSQL_BIND* bind_out;
	MYSQL_RES* res;
	
	MYSQL_FIELD* field;
	
	my_bool isNull=0;
	my_bool isNotNull=1;
	my_ulonglong  affected_rows;

	
	public:
	
	MySQL() : bind_in(0)
	{
		if ( !(mysql = mysql_init(0)) )
		{
			fprintf(stderr, "Failed to instantiate database object: Error: %s\n", mysql_error(mysql) );
		};
	};
	
	int connect( const char* host, 
				  const char* user, 
				  const char* passwd,
				  const char* db, 
				  unsigned int port, 
				  const char* unix_socket, 
				  unsigned long client_flag,
				  const char* charset )
	{
		mysql_set_character_set( mysql , charset );
		mysql_real_connect( mysql, host, user, passwd, db, port, unix_socket, client_flag );
		
		return 0;
	};
	
	void prepareQuery( const char* query )
	{
		stmt = mysql_stmt_init( mysql );	
		
		if ( !stmt )
		{
			fprintf(stderr, "mysql_stmt_init(), out of memory\n");
		}
		
		if ( mysql_stmt_prepare(stmt, query, strlen(query)))
		{
			fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
		}
		
		int n = mysql_stmt_param_count( stmt );
		bind_in = new MYSQL_BIND[ n ];
		memset(bind_in, 0, sizeof(MYSQL_BIND)*n );
	};
	

	void bindInteger(){};
	void bindFloat(){};
	
	void bindString( uint nparam, const char* value )
	{
		static ulong size = strlen(value);
		static my_bool isNotNull = 0;
		
		
		
		if ( nparam > 0 && nparam <= mysql_stmt_param_count(stmt) )
		{
			if ( size == 0 )
			{
				bind_in->buffer_type = MYSQL_TYPE_NULL;
			}
			else
			{			
				//ojo,... corrompe el puntero si es nparam y no nparam-1
				bind_in += (nparam-1)*sizeof(MYSQL_BIND);
				bind_in->buffer_type = MYSQL_TYPE_STRING;
				bind_in->buffer = (void *)value;
				bind_in->buffer_length = size;
				bind_in->length = &size;
				bind_in->is_null = &isNotNull;
			}
			
		};
	}
	
	void execute()
	{
		if ( mysql_stmt_bind_param(stmt, bind_in) != 0) 
		{
			fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
		}
		
		mysql_stmt_bind_param(stmt, bind_in );
		mysql_stmt_execute(stmt);
		
		
		
		//required to extract cstring lenght for allocating
		mysql_stmt_attr_set(stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &isNotNull );
		
		//store result set on client buffer (mysql-handled)
		mysql_stmt_store_result(stmt);
		
		//affected rows
		//if exists resultset, this function must be called after store_result()
		//if no exist result set this function must be called after execute()
		//cout << "AFFECTED ROWS" << mysql_stmt_affected_rows(stmt) << endl;
		
		if ( (res = mysql_stmt_result_metadata(stmt)) )
		{
			cout << "AFFECTED ROWS" << res << "  " << mysql_stmt_affected_rows(stmt) << endl;
			//result set
			uint ncolumns = mysql_num_fields(res);
			
			//array of buffers ( n pointers as n columns )
			void* buffers[ncolumns];
			long unsigned int* lengths[ncolumns];
			
			//int mysql_stmt_fetch_column(stmt, MYSQL_BIND *bind, unsigned int column, unsigned long offset)

			uint rows = mysql_stmt_affected_rows(stmt);
			cout << rows << "<- number of rows" << endl;

			//array of bind_out ( n binds as n columns )
			bind_out = new MYSQL_BIND[ncolumns];
			
			
			
			for ( uint n = 0; n < ncolumns; n++ )
			{
				lengths[n] = new long unsigned int(field->max_length);
				field = mysql_fetch_field(res);
				buffers[n] = malloc( field->max_length );
				memset( buffers[n], 0, field->max_length );
				
				bind_out[n].buffer_type = MYSQL_TYPE_STRING;
				bind_out[n].buffer= buffers[n];
				bind_out[n].buffer_length = field->max_length;
				bind_out[n].length= lengths[n];
				cout << "binding buffer size: "<< field->max_length << endl;
				//showInfoForColumn(field, n);
				
				//switch( field->type )
				//{
				   //case MYSQL_TYPE_TINY :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_SHORT  :
					  //cout << "HANDLED!" << endl;
					  //break;
					
					//case MYSQL_TYPE_LONG :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_INT24  :
					  //cout << "HANDLED!" << endl;
					  //break;
					
					//case MYSQL_TYPE_LONGLONG :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_NEWDECIMAL  :
					  //cout << "HANDLED!" << endl;
					  //break;
					  
					  //case MYSQL_TYPE_FLOAT :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_DOUBLE  :
					  //cout << "HANDLED!" << endl;
					  //break;
					  
					  //case MYSQL_TYPE_BIT :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_TIMESTAMP  :
					  //cout << "HANDLED!" << endl;
					  //break;
					  
					  //case MYSQL_TYPE_DATE :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_TIME  :
					  //cout << "HANDLED!" << endl;
					  //break;
				   
				   //case MYSQL_TYPE_DATETIME :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_YEAR  :
					  //cout << "HANDLED!" << endl;
					  //break;
					  
					  //case MYSQL_TYPE_STRING :
					  //cout << "HANDLED!" << endl;
					  //static char string_buffer[256];
					  //memset( string_buffer, 0, 256);
					  //bind_out->buffer_type = MYSQL_TYPE_STRING;
						//bind_out->buffer= (char *)string_buffer;
						//bind_out->buffer_length= 256;
						//bind_out->is_null= 0;
						//bind_out->length= 256;
					  
					  //break;
					
				   //case MYSQL_TYPE_VAR_STRING  :
					  //cout << "HANDLED!" << endl;
					  //break;
					  
					  //case MYSQL_TYPE_BLOB :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_SET  :
					  //cout << "HANDLED!" << endl;
					  //break;
					  
					  //case MYSQL_TYPE_ENUM :
					  //cout << "HANDLED!" << endl;
					  //break;
					
				   //case MYSQL_TYPE_GEOMETRY  :
					  //cout << "HANDLED!" << endl;
					  //break;
				   
				   //case MYSQL_TYPE_NULL :
						//cout << "HANDLED!" << endl;
					//break;
				   
				   //default : 
				   //cout << "CANNOT HANDLE TYPE OF COLUMN" << endl;
				//}
			};	
			
			mysql_stmt_bind_result(stmt, bind_out );
			
			int error_stmt_fetch = 0;
			
			while( !( error_stmt_fetch = mysql_stmt_fetch(stmt) ) )
			{
				if ( error_stmt_fetch != 0 )
					cout << "error: ";
				else
					cout << "sucessfully";
				
			};
			
						
			for ( uint n = 0; n < ncolumns; n++ )
			{
				free( buffers[n] );
			};
			
		} else
		{
			cout << "no resultSet" << endl;
			
			
			
			affected_rows = mysql_stmt_affected_rows(stmt);
			cout << "affected : " << (long long )affected_rows;
						fprintf(stderr, " %s\n", mysql_stmt_error(stmt));

		};
		
		
		cout << "FINISHED" << endl;
		
	};
	
	void fetch(){};
	
	~MySQL()
	{
		 mysql_stmt_close(stmt) ;
		 delete[] bind_in;
		 //delete bind_out;
		 mysql_stmt_free_result(stmt);
		 mysql_close(mysql);
	}
	
};

void printMysqlTypes()
{
	cout << "MYSQL_TYPE_TINY -> " << MYSQL_TYPE_TINY << endl;
	cout << "MYSQL_TYPE_SHORT -> " << MYSQL_TYPE_SHORT << endl;
	cout << "MYSQL_TYPE_LONG -> " << MYSQL_TYPE_LONG << endl;
	cout << "MYSQL_TYPE_INT24 -> " << MYSQL_TYPE_INT24 << endl;
	cout << "MYSQL_TYPE_LONGLONG -> " << MYSQL_TYPE_LONGLONG << endl;
	cout << "MYSQL_TYPE_DECIMAL -> " << MYSQL_TYPE_DECIMAL << endl;
	cout << "MYSQL_TYPE_NEWDECIMAL -> " << MYSQL_TYPE_NEWDECIMAL << endl;
	cout << "MYSQL_TYPE_FLOAT -> " << MYSQL_TYPE_FLOAT << endl;
	cout << "MYSQL_TYPE_DOUBLE -> " << MYSQL_TYPE_DOUBLE << endl;
	cout << "MYSQL_TYPE_BIT -> " << MYSQL_TYPE_BIT << endl;
	cout << "MYSQL_TYPE_TIMESTAMP -> " << MYSQL_TYPE_TIMESTAMP << endl;
	cout << "MYSQL_TYPE_DATE -> " << MYSQL_TYPE_DATE << endl;
	cout << "MYSQL_TYPE_TIME -> " << MYSQL_TYPE_TIME << endl;
	cout << "MYSQL_TYPE_DATETIME -> " << MYSQL_TYPE_DATETIME << endl;
	cout << "MYSQL_TYPE_YEAR -> " << MYSQL_TYPE_YEAR << endl;
	cout << "MYSQL_TYPE_STRING -> " << MYSQL_TYPE_STRING << endl;
	cout << "MYSQL_TYPE_VAR_STRING -> " << MYSQL_TYPE_VAR_STRING << endl;
	cout << "MYSQL_TYPE_BLOB -> " << MYSQL_TYPE_BLOB << endl;
	cout << "MYSQL_TYPE_SET -> " << MYSQL_TYPE_SET << endl;
	cout << "MYSQL_TYPE_ENUM -> " << MYSQL_TYPE_ENUM << endl;
	cout << "MYSQL_TYPE_BIT -> " << MYSQL_TYPE_BIT << endl;
	cout << "MYSQL_TYPE_GEOMETRY -> " << MYSQL_TYPE_GEOMETRY << endl;
	cout << "MYSQL_TYPE_NULL -> " << MYSQL_TYPE_NULL << endl;

}

int main()
{
	printMysqlTypes();
	
	MySQL db;
	db.connect( "localhost", "root", "987654", "ccm", MYSQL_PORT, NULL, 0, "utf8" );
	//db.prepareQuery( "INSERT INTO actions(name) VALUE(?)" );
	//db.bindString( 1, "testing" );
	db.prepareQuery("SELECT * FROM actions");
	//db.bindString(1, "2");
	db.execute();
	

	
	return 0;
}
