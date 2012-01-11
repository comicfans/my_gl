/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestRotate.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 23:27:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "MyGLTestTpl.hpp"
#include "TestRotate.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;


int main(int argc, const char *argv[])
{
     myGLTestRun<SoftContext,TestRotate>();
}
