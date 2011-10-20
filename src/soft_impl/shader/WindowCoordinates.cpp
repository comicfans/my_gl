/*
 * =====================================================================================
 *
 *       Filename:  WindowCoordinates.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-20 22:25:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "WindowCoordinates.hpp"

namespace my_gl {
	
	  int& WindowCoordinates::operator[](int index)
	  {
	       return index==0?first:second;

	  }

	  const int& WindowCoordinates::operator[](int index)const{
	       return index==0?first:second;
	  }

} /* my_gl */
