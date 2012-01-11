/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestScale.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-11 8:42:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "MyGLTestTpl.hpp"
#include "soft_impl/SoftContext.hpp"
#include "TestScale.hpp"

using namespace my_gl;


int main(int argc, const char *argv[])
{

     myGLTestRun<SoftContext,TestScale>();
}

