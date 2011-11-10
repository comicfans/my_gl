/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestClientArrayPointer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 19:28:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "soft_impl/SoftContext.hpp"
#include "common/Context.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include "TestClientArrayPointer.hpp"

using namespace my_gl;

SoftContext context(DEFAULT_WIDTH,DEFAULT_HEIGHT);

int main(int argc, const char *argv[])
{

     TestClientArrayPointer::init();

     for (int i=0; i<10; ++i)
     {
	  TestClientArrayPointer::render();
	  glFlush();
     }
     
	
	return 0;
}

