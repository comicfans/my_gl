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

#include "TestArrayBufferObject.hpp"

using namespace my_gl;

int main(int argc, char *argv[])
{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

     glutInitWindowSize(400,300);

     glutCreateWindow("GlutTestArrayBufferObject");

     glutDisplayFunc(TestArrayBufferObject::render);

     glewInit();

     TestArrayBufferObject::init(400,300);

     glutMainLoop();
	
     return 0;
}

