/*
 * =====================================================================================
 *
 *       Filename:  UniqueVec4Provider.cpp
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
#include "UniqueVec4Provider.hpp"

namespace my_gl {

     UniqueVec4Provider::UniqueVec4Provider
	  (const Vec4& value)
	  :_value(value){}

	
     Vec4 UniqueVec4Provider::getValue(size_t index)
     {
	  return _value;
     }

     void UniqueVec4Provider::setValue(const Vec4& value)
     {
	  _value=value;
     }

} /* my_gl */

