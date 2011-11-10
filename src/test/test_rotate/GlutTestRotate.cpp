/*
 * =====================================================================================
 *
 *       Filename:  GlutTestRotate.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 23:22:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "GlutInit.hpp"

#include <gl/glew.h>
#include <gl/glut.h>
#include "TestRotate.hpp"

using namespace my_gl;

static void idleFunc()
{

     glutSwapBuffers();
     glutPostRedisplay();
}

int main(int argc, const char *argv[])
{
     initGlutGlew();

     glutDisplayFunc(TestRotate::render);

     glutIdleFunc(idleFunc);

     TestRotate::init();
	
     glutMainLoop();

     return 0;
}
