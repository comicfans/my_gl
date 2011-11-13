/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestPerspectiveProject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-13 22:33:13
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
#include "TestPerspectiveProject.hpp"

using namespace my_gl;

SoftContext context(DEFAULT_WIDTH,DEFAULT_HEIGHT);

int main(int argc, const char *argv[])
{
     TestPerspectiveProject::init();
     for (int i=0; i<300; ++i)
     {
	  TestPerspectiveProject::render();
	  glFlush();
     }
     

	
}
