/*
 * =====================================================================================
 *
 *       Filename:  GlutTestLighting.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-14 8:51:37
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

#include "TestLighting.hpp"

using namespace my_gl;

static void display(int)
{

     TestLighting::render();
     glutSwapBuffers();
      
     glutTimerFunc(500,display,0);

}
 int main(int argc, const char *argv[])
 {
      initGlutGlew();

      TestLighting::init();

      glutTimerFunc(500,display,0);

      glutMainLoop();
 	
      return 0;
 }
