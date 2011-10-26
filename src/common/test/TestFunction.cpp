/*
 * =====================================================================================
 *
 *       Filename:  TestFunction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-26 11:19:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TestFunction.hpp"

#include <cmath>

#include "common/Vec4.hpp"

namespace my_gl {
     
     using std::abs;
	     
     bool equal(float lhs,float rhs)
     {
	  return abs(lhs-rhs)<=abs(lhs)/10000;
     }

     bool equal (const Vec4& lhs,const Vec4& rhs)
     {
	  bool prevEqual=true;
	  for (size_t i=0; i<Vec4::LENGTH; ++i)
	  {
	       prevEqual=equal(lhs[i],rhs[i]);
	       if (!prevEqual)
	       {
		    return false;
	       }
	  }
	  return true;
     }
	
} /* my_gl */
