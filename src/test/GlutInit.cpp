/*
 * =====================================================================================
 *
 *       Filename:  GlutInit.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 19:30:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "GlutInit.hpp"

#include <GL/glew.h>
#include <GL/glut.h>

namespace my_gl {
     void initGlutGlew(const char* p)
     {
	  int argc=0;
     glutInit(&argc, nullptr);

     glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

     glutInitWindowSize(DEFAULT_WIDTH,DEFAULT_HEIGHT);

     glutCreateWindow(p);

     glewInit();


     }

     void idleFunc()
     {
	  glutSwapBuffers();
	  glutPostRedisplay();
     }
} /* my_gl */
