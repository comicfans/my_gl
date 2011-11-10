/*
 * =====================================================================================
 *
 *       Filename:  GlutTest.cpp
 *
 *    Description:  use glut and glew 
 *
 *        Version:  1.0
 *        Created:  2011-11-10 13:56:21
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

#include "GlutInit.hpp"
#include "TestArrayBufferObject.hpp"

using namespace my_gl;

static void idleFunc()
{
     glutSwapBuffers();
     glutPostRedisplay();

}
int main(int argc, char *argv[])
{
     initGlutGlew("GlutTestArrayBufferObject");

     glutDisplayFunc(TestArrayBufferObject::render);

     glutIdleFunc(idleFunc);

     TestArrayBufferObject::init();

     glutMainLoop();
	
     return 0;
}

