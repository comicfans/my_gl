/*
 * =====================================================================================
 *
 *       Filename:  UniqueVectorProvider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-19 13:03:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "UniqueVectorProvider.hpp"

namespace my_gl {

     Vector UniqueVectorProvider::value()noexcept
     {
	  return _value;
     }

     void UniqueVectorProvider::setValue(const Vector& value)noexcept
     {
	  _value=value;
     }
	
} /* my_gl */

