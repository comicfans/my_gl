/*
 * =====================================================================================
 *
 *       Filename:  OpenCLImplTestPoints.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-8 18:59:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "MyGLTestTpl.hpp"
#include "opencl_impl/OpenCLContext.hpp"
#include "TestPoints.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     myGLTestRun<OpenCLContext,TestPoints>();
}

