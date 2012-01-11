/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestClientArrayPointer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 19:28:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "MyGLTestTpl.hpp"
#include "TestClientArrayPointer.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;


int main(int argc, const char *argv[])
{

     myGLTestRun<SoftContext,TestClientArrayPointer>();
}

