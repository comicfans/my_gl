/*
 * =====================================================================================
 *
 *       Filename:  CheckEnum.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/2/18 19:36:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "CheckEnum.hpp"

#include <cassert>
#include <algorithm>

namespace my_gl {

     using std::find;

     bool checkDataType(GLenum value)
     {
	  GLenum validValues[]={GL_BYTE,GL_UNSIGNED_BYTE,GL_SHORT,GL_UNSIGNED_SHORT,GL_FIXED,GL_FLOAT};

	  int arrayLength=sizeof(validValues)/sizeof(GLenum);
	  assert(find(validValues,validValues+arrayLength,value)!=validValues+arrayLength
		    || "wrong data value enum ");

	  return true;
     }

     bool checkPrimitiveMode(GLenum value)
     {

	  GLenum validValues[]={GL_POINTS,GL_LINES,GL_TRIANGLES,
	       GL_LINE_STRIP,GL_LINE_LOOP,GL_TRIANGLE_STRIP,GL_TRIANGLE_FAN};

	  int arrayLength=sizeof(validValues)/sizeof(GLenum);

	  assert(find(validValues,validValues+arrayLength,value)!=validValues+arrayLength
		    || "wrong data value enum ");

	  return true;
     }
	
} /* my_gl */
