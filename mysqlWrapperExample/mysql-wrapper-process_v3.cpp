#include <iostream>
#include <list>
#include <vector>
#include <dlfcn.h>
#include <string.h>
#include <mysql/mysql.h>

using namespace std;


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
	
	void* buffer_out;
	void* buffer_out_lenght;
	
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
	
	bool existResultSet( )
	{
		return ( !res )? false : true;
	};
	
	void bindParameters()
	{
		mysql_stmt_bind_param(stmt, bind_in);
	};

	void executeRequest()
	{
		mysql_stmt_execute(stmt);
	};
	
	void storeExecutionResultOnServer()
	{
			mysql_stmt_store_result(stmt);
	
	};
	
	void getMetadata()
	{
				res = mysql_stmt_result_metadata(stmt);
	};
	
	void setOptions()
	{
				mysql_stmt_attr_set(stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &isNotNull );
	};
	
	void* bindResultBuffer(  )
	{
		
		//uint ncolumns = mysql_num_fields(res);
				
		//bind_out = new MYSQL_BIND[ncolumns];
		
		//for ( uint n = 0; n < ncolumns; n++ )
			//{
				//lengths[n] = new long unsigned int(field->max_length);
				//field = mysql_fetch_field(res);
				//buffers[n] = malloc( field->max_length );
				//memset( buffers[n], 0, field->max_length );
				
				//bind_out[n].buffer_type = MYSQL_TYPE_STRING;
				//bind_out[n].buffer= buffers[n];
				//bind_out[n].buffer_length = field->max_length;
				//bind_out[n].length= lengths[n];
				////cout << "binding buffer size: "<< field->max_length << endl;
				//showInfoForColumn(field, n);
				
			//};	


		return 0;
	};
	
	int fetchingResults()
	{
		cout << "fetching result..." << endl;
		return mysql_stmt_fetch(stmt);
	};
	
	void execute()
	{
		mysql_stmt_bind_param(stmt, bind_in);
		
		// Reauest meta data information
		res = mysql_stmt_result_metadata(stmt);
		uint nfields = mysql_num_fields(res);
		bind_out = new MYSQL_BIND[nfields];
		
		// Set STMT_ATTR_UPDATE_MAX_LENGTH attribute
		my_bool aBool = 1;
		mysql_stmt_attr_set(stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &aBool);

		/* Execute the select statement - 1*/
		if (mysql_stmt_execute(stmt))
		{
		  fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
		  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
		  exit(0);
		}

		if (mysql_stmt_store_result(stmt)) {
		  fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
		  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
		  exit(0);
		}       

		// Retrieving meta data information
		MYSQL_FIELD* aField = &res->fields[0];

		fprintf(stdout, " field %s \n",aField->name);
		fprintf(stdout, " field length %d \n",(int) aField->length);
		fprintf(stdout, " field max length %d \n", (int) aField->max_length);


		int totalrows = mysql_stmt_num_rows(stmt);
		fprintf(stdout, " fetched %d description\n",totalrows);
		fprintf(stdout, " field count %d \n",(int) res->field_count);

		long unsigned int aMaxSize;
		//char* aBuffer = (char*) malloc(aField->max_length);
		static char aBuffer[70000];
		memset (bind_out, 0, sizeof (MYSQL_BIND)*nfields );
		bind_out[0].buffer_type= MYSQL_TYPE_STRING;
		bind_out[0].is_null= 0;
		bind_out[0].buffer= (char *) aBuffer;
		bind_out[0].buffer_length= aField->max_length;
		bind_out[0].length= &aMaxSize;

		mysql_stmt_bind_result(stmt, bind_out);

		std::string aStrData;
		while(!mysql_stmt_fetch(stmt))
		{
			fprintf(stdout, " size %d\n", (int) aMaxSize);
    //aStrData = std::string(aBuffer,aMaxSize);
    printf("%.*s", aMaxSize, aBuffer );

    //fprintf(stdout, " data %s\n", aStrData.c_str());
		}

		//free(aBuffer);

		mysql_free_result(res);
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
	//printMysqlTypes();
	
	MySQL db;
	db.connect( "localhost", "root", "987654", "ccm", MYSQL_PORT, NULL, 0, "utf8" );
	//db.prepareQuery( "INSERT INTO actions(name) VALUE(?)" );
	//db.bindString( 1, "testing" );
	db.prepareQuery("SELECT name FROM actions ORDER BY id");
	//db.bindString(1, "2");
	db.execute();
	
	
	
	return 0;
}
