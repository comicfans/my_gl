/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestDrawElements.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-13 14:20:49
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
#include "soft_impl/SoftContext.hpp"
#include "TestDrawElements.hpp"

using namespace my_gl;

SoftContext context(DEFAULT_WIDTH,DEFAULT_HEIGHT);

int main(int argc, const char *argv[])
{
	
     TestDrawElements::init();

     for (int i=0; i<100; ++i)
     {
	  TestDrawElements::render();

	  glFlush();
     }

}
