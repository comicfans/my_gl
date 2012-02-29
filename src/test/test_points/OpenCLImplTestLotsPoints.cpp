/*
 * =====================================================================================
 *
 *       Filename:  OpenCLImplTestLotsPoints.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/2/29 18:47:11
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
#include "TestLotsPoints.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     myGLTestRun<OpenCLContext,TestLotsPoints>();
}

