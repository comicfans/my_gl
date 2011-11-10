/*
 * =====================================================================================
 *
 *       Filename:  GlutTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 19:23:33
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
#include "TestClientArrayPointer.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     initGlutGlew();

     glutDisplayFunc(TestClientArrayPointer::render);

     TestClientArrayPointer::init();

     glutMainLoop();
	
	return 0;
}

