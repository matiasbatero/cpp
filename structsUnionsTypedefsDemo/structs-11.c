/*
 * Playing with structs, unions, typedefs and *pointers!
 * =====================================================
 * 
 * Copyright 2014 matt <matt@matt>
 * Matías Gastón Santiago.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_PROFILE 20
#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define MAX_IP 11

typedef struct connection connection;
typedef enum states {connected, disconnected} cc_state;
typedef enum type {pppoe, wired} cc_type;
typedef char user[MAX_USERNAME];
typedef char pass[MAX_PASSWORD];
typedef char ipaddr[MAX_IP];
typedef char profile[MAX_NAME_PROFILE];
typedef union c_type c_type;
typedef struct networking networking;

//definition of connection
struct connection
{
	profile nameid;
	cc_state active;
		
	union c_type  //"pseudo polymorphism"
	{
		struct c_pppoe
		{
			user username;
			pass password;
			//level 2 : functionalities
			void (*SetPassword)(connection *, pass);
			void (*SetUsername)(connection *, user);
			void (*Connect)(connection *);
		} pppoe;
	
		struct c_wired
		{
			ipaddr ip;
			void (*SetIp)(connection *, ipaddr);
			void (*Connect)(connection *);
		} wired;
	} settings;
	
	//level 1 : general functionalities
	void (*SetTypeConnection)(connection *, cc_type value);
	void (*Connect)(connection *);
};


//associated functions Level 2
void SetUsername(connection *input, user value)
{
	strcpy(input->settings.pppoe.username, value); //encapsulate this.
};

void SetPassword(connection *input, pass value)
{
	strcpy(input->settings.pppoe.password, value); //encapsulate this.
};

void SetIp(connection *input, ipaddr value)
{
	strcpy(input->settings.wired.ip, value);
}

//associated functions level 1
void SetTypeConnection(connection *input, cc_type value)
{
	if ( value == pppoe ) 
	{
		input->active=value;
		input->settings.pppoe.SetPassword=&SetPassword; //revision
		input->settings.pppoe.SetUsername=&SetUsername;
	};
	
	if ( value == wired )
	{
		input->active=value;
		input->settings.wired.SetIp=&SetIp;
		
	};
		
};

//general structure
struct networking
{
	void (*LoadFunctions)(networking *);
	connection *(*CreateConnection)(void);
};


//function to create connections
connection *CreateConnection(void)
{
	connection *new;
	new = (connection*)malloc(sizeof(connection));
	
	//initialize own associated functions (level 1)
	new->SetTypeConnection=&SetTypeConnection;
	
	//etc..
	
	return new;
};


//this function load the networking operations
void NetworkFunctionality(networking *input)
{
	input->CreateConnection=&CreateConnection;
};

//declare network
networking network;
	
	
int main()
{
	
	//declaration, assign behavior and load behavior.
	network.LoadFunctions=&NetworkFunctionality;
	network.LoadFunctions(&network);
	
	//testing
	connection *newtest;
	newtest = network.CreateConnection();
	
	newtest->SetTypeConnection(newtest, pppoe);
	newtest->settings.pppoe.SetUsername(newtest, "49921200@speedy");
	newtest->settings.pppoe.SetPassword(newtest, "pass12345");
	
	//print results of test
	printf("Name: %s \n", newtest->settings.pppoe.username);
	printf("Password: %s \n", newtest->settings.pppoe.password);
	
	return 0;
}
