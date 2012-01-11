/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestCullFaceBack.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-14 8:44:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "MyGLTestTpl.hpp"
#include "TestCullFaceBack.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
	
     myGLTestRun<SoftContext,TestCullFaceBack>();
}
