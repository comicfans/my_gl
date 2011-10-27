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
#include <iostream>
#include <cassert>

#include "common/Vec4.hpp"

namespace my_gl {
     
     using std::abs;
     using std::cout;
     using std::endl;
	     
     bool equal(float lhs,float rhs)
     {
	  return abs(lhs-rhs)<=abs(lhs)/10000;
     }

     void assertEqual(float lhs,float rhs)
     {
	  if (!equal(lhs,rhs))
	  {
	       cout<<"lhs is "<<lhs<<" but rhs is "<<rhs<<endl;
	       assert(false);
	  }
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
