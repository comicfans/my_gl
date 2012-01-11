/*
 * =====================================================================================
 *
 *       Filename:  OpenCLImplTestClientArrayPointer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-10 20:58:51
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
#include "TestClientArrayPointer.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     myGLTestRun<OpenCLContext,TestClientArrayPointer>();
}
