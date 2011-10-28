/*
 * =====================================================================================
 *
 *       Filename:  testMatrix.cpp
 *
 *    Description:  test matrix functions
 *
 *        Version:  1.0
 *        Created:  2011-10-28 12:58:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <climits>
#include "common/Matrix.hpp"

#include "TestFunction.hpp"


using namespace my_gl;


static Matrix randMatrix()
{

     Matrix matrix;

     for(int i=0;i<Matrix::LENGTH;++i)
     {
	  for (int j=0; j<Matrix::LENGTH; ++j)
	  {
	       matrix(i,j)=float(myRand())/INT_MAX;
	  }
     }

     return matrix;

}

void testTranspose()
{
     Matrix matrix=randMatrix();

     assertEqual(matrix,matrix.transpose().transpose());
}

void testIdentityMul()
{
     Matrix matrix=randMatrix();

     Matrix identity=Matrix::identity();

     Matrix shouldSame1=matrix*identity,
	    shouldSame2=identity*matrix;

     assertEqual(shouldSame1,shouldSame2);
     assertEqual(shouldSame1,matrix);
}

void testInverse(int gen=1)
{

     Matrix matrix=randMatrix();

     Matrix inverse=matrix.inverse();

     Matrix shouldIdentity=matrix*inverse; 

     assertEqual(shouldIdentity,Matrix::identity());


}

int main(int argc, const char *argv[])
{

     for (int i=0; i<1000; ++i)
     {
	  testTranspose();
	  testIdentityMul();
	  testInverse(100);
     }

}
