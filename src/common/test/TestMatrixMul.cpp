/*
 * =====================================================================================
 *
 *       Filename:  TestMatrixMul.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-3 14:50:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "common/Matrix.hpp"
#include "common/test/TestFunction.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     Matrix4 ran=randMatrix();

     Matrix4 identity=Matrix4::identity();

     Matrix4 shouldSame=ran*identity;
     Matrix4 shouldSame2=identity*ran;

     assertEqual(shouldSame,ran);
     assertEqual(shouldSame2,ran);
	
	return 0;
}
