/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestPerspectiveProject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-13 22:33:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "MyGLTestTpl.hpp"
#include "TestCullFace.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;


int main(int argc, const char *argv[])
{
     myGLTestRun<SoftContext,TestCullFace>();
}
