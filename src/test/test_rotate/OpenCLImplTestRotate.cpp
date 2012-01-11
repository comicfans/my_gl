/*
 * =====================================================================================
 *
 *       Filename:  OpenCLImplTestRotate.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-10 21:04:58
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
#include "TestRotate.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     myGLTestRun<OpenCLContext,TestRotate>();
}

