/*
 * =====================================================================================
 *
 *       Filename:  UniqueNormalProvider.cpp
 *
 *    Description:  implementation of UniqueNormalProvider
 *
 *        Version:  1.0
 *        Created:  2011-9-14 16:25:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "UniqueNormalProvider.hpp"

namespace my_gl {

     Vector UniqueNormalProvider::get()
     {
	  return _normal;
     }

     void UniqueNormalProvider::set(my_gl::Vector normal)
     {
	  _normal=normal;
     }
	
} /* my */
