/*
 * =====================================================================================
 *
 *       Filename:  TestMatrixInverse.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-3 12:39:13
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
void testInverse()
{

     Matrix4 matrix=randMatrix();

     Matrix4 inverse=matrix.inverse();

     Matrix4 shouldIdentity=matrix*inverse; 

     assertEqual(shouldIdentity,Matrix4::identity());


}

void testIdentity()
{
     Matrix4 identity=Matrix4::identity();

     assertEqual(identity.inverse(),identity);

}


int main(int argc, const char *argv[])
{
	
     testIdentity();
     for (int i=0; i<300; ++i)
     {
	  testInverse();
     }

}
