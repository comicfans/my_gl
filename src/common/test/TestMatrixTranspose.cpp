/*
 * =====================================================================================
 *
 *       Filename:  TestMatrixTranspose.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-3 12:40:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "common/test/TestFunction.hpp"
using namespace my_gl;

void testTranspose()
{
     Matrix4 matrix=randMatrix();

     assertEqual(matrix,matrix.transpose().transpose());
}


int main(int argc, const char *argv[])
{
	
     for (int i=0; i<300; ++i)
     {
	  testTranspose();
     }
}
