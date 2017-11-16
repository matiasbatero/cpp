/*
 * main.cpp
 * 
 * Copyright 2017 matt <matt@DESKTOP-LAL38J2>
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
#include <cstring>

using namespace std;

struct typeSchema;
struct typeMetadata;
struct objectField;

struct typeMetadata
{
	const uint32_t	id;
	const char*		name;
	const uint32_t	sizeOf;
	const typeSchema& schema;
};

struct typeSchema
{
	const uint32_t		id;
	const uint32_t		fields;
	const objectField*	fieldMembers;
};

struct objectField
{
	const uint32_t		id;
	const char*			name;
	const typeMetadata&	typeMetadataId;
};

const typeSchema& none()
{
	static const typeSchema def =
	{
		.id = 0,
		.fields = 0
	};
	
	return def;
};

const typeMetadata& integer()
{
	static const typeMetadata def =
	{
		.id = 1,
		.name = "integer",
		.sizeOf = sizeof(int),
		.schema = none()
	};
	
	return def;
};

const typeMetadata& object()
{
	static const typeMetadata def =
	{
		.id = 2,
		.name = "object",
		.sizeOf = sizeof(int),
		.schema = none()
	};
	
	return def;
};

const typeMetadata& userDefined()
{
	static const objectField userDefinedFields[] =
	{
		{
			.id = 0,
			.name = "Identity",
			.typeMetadataId = integer()
		},
		{
			.id = 1,
			.name = "Identity2",
			.typeMetadataId = integer()
		}
	};
	
	static const typeSchema userDefinedSchema =
	{
		.id = 1,
		.fields = 2,
		.fieldMembers = userDefinedFields
	};
	
	static const typeMetadata def =
	{
		.id = 2,
		.name = "userDefined",
		.sizeOf = sizeof(int),
		.schema = userDefinedSchema		
	};
	
	return def;
};

void inspectField( const objectField& field )
{
	//if( field.typeMetadataId.schema.id != none().id )
	//{
		cout << "<" << field.name << " type=" << field.typeMetadataId.name << ">" << "</>" << endl;
	//};
	
};

void inspect( const typeMetadata& type )
{
	if ( type.schema.id != none().id )
	{
		cout << type.name << endl;
		
		for( uint32_t i = 0; i < type.schema.fields ; i++ )
			inspect( (*(type.schema.fieldMembers+0)).typeMetadataId) ;
		
	}
	else
	{
		cout << "<"<< type.name << endl;
	};
};

int main(int argc, char **argv)
{
	//inspect( userDefined() );
	inspectField( (*(userDefined().schema.fieldMembers + 0)) );
	inspectField( (*(userDefined().schema.fieldMembers + 1)) );
	
	return 0;
}

