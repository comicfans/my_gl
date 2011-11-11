/*
 * =====================================================================================
 *
 *       Filename:  GlutTestScale.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-11 8:26:52
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
#include "TestScale.hpp"
#include "GlutInit.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{

     initGlutGlew();

     glutIdleFunc(idleFunc);

     glutDisplayFunc(TestScale::render);

     TestScale::init();

     glutMainLoop();

     return 0;
}

