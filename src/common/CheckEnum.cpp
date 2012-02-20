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

     bool checkDepthFunc(GLenum value)
     {
	  GLenum validValues[]={GL_NEVER,GL_ALWAYS,GL_EQUAL,
	       GL_NOTEQUAL,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL};

	  int arrayLength=sizeof(validValues)/sizeof(GLenum);
	  assert(find(validValues,validValues+arrayLength,value)!=validValues+arrayLength
		    || "wrong data value enum ");

	  return true;
     }


     bool checkDataType(GLenum value)
     {
	  GLenum validValues[]={GL_BYTE,GL_UNSIGNED_BYTE,GL_SHORT,GL_UNSIGNED_SHORT,GL_FIXED,GL_FLOAT};

	  int arrayLength=sizeof(validValues)/sizeof(GLenum);
	  assert(find(validValues,validValues+arrayLength,value)!=validValues+arrayLength
		    || "wrong data value enum ");

	  return true;
     }

     bool checkBindState(GLenum value)
     {
	  GLenum validValues[]={GL_VERTEX_ARRAY,GL_NORMAL_ARRAY,
	       GL_COLOR_ARRAY,GL_TEXTURE_COORD_ARRAY};

	  int arrayLength=sizeof(validValues)/sizeof(GLenum);
	  assert(find(validValues,validValues+arrayLength,value)!=validValues+arrayLength
		    || "wrong data value enum ");

	  return true;
     }

     bool checkLightN(GLenum value)
     {
	  GLenum validValues[]={GL_LIGHT0,GL_LIGHT1,
	       GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,
	       GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};

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

     bool checkNormalize(GLenum value)
     {
	  GLenum validValues[]={GL_NORMALIZE,GL_RESCALE_NORMAL};

	  int arrayLength=sizeof(validValues)/sizeof(GLenum);

	  assert(find(validValues,validValues+arrayLength,value)!=validValues+arrayLength
		    || "wrong normalized normal value enum ");

	  return true;
 
     }
	
} /* my_gl */
