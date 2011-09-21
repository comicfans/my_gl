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

     UniqueVectorProvider::UniqueVectorProvider
	  (const Vector& value)noexcept
	  :_value(value){}

     Vector UniqueVectorProvider::value()noexcept
     {
	  return _value;
     }

     void UniqueVectorProvider::setValue(const Vector& value)noexcept
     {
	  _value=value;
     }

     void UniqueVectorProvider::next(size_t steps)noexcept
     {}
	
} /* my_gl */

