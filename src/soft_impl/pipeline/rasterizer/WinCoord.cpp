/*
 * =====================================================================================
 *
 *       Filename:  WinCoord.cpp
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

#include "WinCoord.hpp"

namespace my_gl {
	
     WinCoord::WinCoord(int y,int x)
	  :pair<int,int>(y,x)
	  {

	  }
	  int& WinCoord::operator[](int index)
	  {
	       return index==0?first:second;

	  }

	  const int& WinCoord::operator[](int index)const{
	       return index==0?first:second;
	  }

} /* my_gl */
