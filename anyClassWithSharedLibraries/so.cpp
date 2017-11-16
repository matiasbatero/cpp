/* Any class across DLL boundary
 * Study and Code in progress
 * 
 * Matías Gastón Santiago
 * 
 */

#include "./src/any.hpp"

extern "C" any create()
{
	return new std::string("Hi from DLL!");
}
