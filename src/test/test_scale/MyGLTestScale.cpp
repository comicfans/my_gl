/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestScale.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-11 8:42:12
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
#include "TestScale.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;

SoftContext softContext(DEFAULT_WIDTH,DEFAULT_HEIGHT);

int main(int argc, const char *argv[])
{

     TestScale::init();

     for (int i=0; i<200; ++i)
     {
	  TestScale::render();
	  glFlush();
     }
     
	
	return 0;
}

