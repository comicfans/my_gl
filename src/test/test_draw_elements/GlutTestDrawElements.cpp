/*
 * =====================================================================================
 *
 *       Filename:  GlutTestDrawElements.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-12 17:56:05
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
#include "TestDrawElements.hpp"

using namespace my_gl;

static void display(int arg)
{
     TestDrawElements::render();
     glutSwapBuffers();

     glutTimerFunc(100,display,1);

}

int main(int argc, const char *argv[])
{

     initGlutGlew();

     glutDisplayFunc(TestDrawElements::render);

     glutTimerFunc(100,display,1);

     TestDrawElements::init();
	
     glutMainLoop();
	return 0;
}
