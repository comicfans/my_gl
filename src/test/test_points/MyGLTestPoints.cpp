/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestPoints.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-8 18:58:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "MyGLTestTpl.hpp"
#include "TestPoints.hpp"
#include "soft_impl/SoftContext.hpp"

using namespace my_gl;


int main(int argc, const char *argv[])
{
     myGLTestRun<SoftContext,TestPoints>();
}
