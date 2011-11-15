/*
 * =====================================================================================
 *
 *       Filename:  GlutTest.cpp
 *
 *    Description:  use glut and glew 
 *
 *        Version:  1.0
 *        Created:  2011-11-10 13:56:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "GlutTestTpl.hpp"
#include "TestArrayBufferObject.hpp"

using namespace my_gl;

int main(int argc, char *argv[])
{
     singleBufferRun<TestArrayBufferObject>();
}

