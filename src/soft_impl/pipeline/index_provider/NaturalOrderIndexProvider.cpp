/*
 * =====================================================================================
 *
 *       Filename:  NaturalOrderIndexProvider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-10 16:46:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "NaturalOrderIndexProvider.hpp"

namespace my_gl {

     NaturalOrderIndexProvider::
	  NaturalOrderIndexProvider(size_t jump)
	  :_jump(jump){}

     NaturalOrderIndexProvider::~NaturalOrderIndexProvider(){}

     size_t NaturalOrderIndexProvider::getIndex(size_t index)const
     {return _jump+index;}

	
} /* my_gl */
