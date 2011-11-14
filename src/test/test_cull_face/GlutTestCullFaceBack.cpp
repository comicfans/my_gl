/*
 * =====================================================================================
 *
 *       Filename:  GlutTestCullFaceBack.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-14 8:42:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <GL/glew.h>
#include <GL/glut.h>
#include "TestCullFaceBack.hpp"

using namespace my_gl;

static void display(int )
{
     TestCullFaceBack::render();
     glutSwapBuffers();
     glutTimerFunc(1000,display,1);
}
int main(int argc, const char *argv[])
{
	
     initGlutGlew();
     TestCullFaceBack::init();
     glutTimerFunc(1000,display,1);
     glutMainLoop();
	return 0;
}
