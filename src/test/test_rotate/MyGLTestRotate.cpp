/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestRotate.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 23:27:51
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

#include "TestRotate.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;

SoftContext context(DEFAULT_WIDTH,DEFAULT_HEIGHT);

int main(int argc, const char *argv[])
{
     TestRotate::init();

     for (int i=0; i<100; ++i)
     {
	  TestRotate::render();
	  glFlush();
     }
     
	
	return 0;
}
