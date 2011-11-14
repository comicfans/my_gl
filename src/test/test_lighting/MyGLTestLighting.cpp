/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestLighting.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-14 15:15:47
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
#include "TestLighting.hpp"

using namespace my_gl;

SoftContext context(DEFAULT_WIDTH,DEFAULT_HEIGHT);


int main(int argc, const char *argv[])
{
     TestLighting::init();

     for (int i=0; i<300; ++i)
     {
	  TestLighting::render();
	  glFlush();
     }
     
	
}
