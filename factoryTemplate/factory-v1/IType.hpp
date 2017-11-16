/* Matías Gastón Santiago:
 * 
 * TDA/TDC/Factory design & implementation
 * 
 * 29/6/2015
 *
 * IType.hpp
 *  
 */

#ifndef ITYPE_HPP
#define ITYPE_HPP

//Interface definition (Abstract Type : TDA)

class IType 
{
	public:
	
	virtual void methodA() = 0;
	virtual void methodB() = 0;
	virtual void methodC() = 0;
	
	virtual ~IType() {}
	
};

#endif
