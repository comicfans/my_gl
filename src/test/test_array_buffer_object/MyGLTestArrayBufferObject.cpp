/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestArrayBufferObject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 15:19:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#include "common/Context.hpp"
#include "soft_impl/SoftContext.hpp"


#include "TestArrayBufferObject.hpp"

using namespace my_gl;

SoftContext context(DEFAULT_WIDTH,DEFAULT_HEIGHT);

int main(int argc, const char *argv[])
{

     TestArrayBufferObject::init();

     for (int i=0; i<30; ++i)
     {
	  TestArrayBufferObject::render();
	  glFlush();
     }
     
	return 0;
}
