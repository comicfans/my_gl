/*
 * =====================================================================================
 *
 *       Filename:  GlutTestPerspectiveProject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-13 22:30:51
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

#include "TestPerspectiveProject.hpp"

#include "GlutInit.hpp"

using namespace my_gl;

static void display(int )
{

     TestPerspectiveProject::render();
     glutSwapBuffers();
     glutTimerFunc(1000,display,1);
}

int main(int argc, const char *argv[])
{

     initGlutGlew();

     TestPerspectiveProject::init();

     glutTimerFunc(1000,display,1);

     glutMainLoop();

	return 0;
}

