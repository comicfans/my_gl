/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestLotsPoints.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/2/29 18:46:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "MyGLTestTpl.hpp"
#include "TestLotsPoints.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;


int main(int argc, const char *argv[])
{
     myGLTestRun<SoftContext,TestLotsPoints>();
}
