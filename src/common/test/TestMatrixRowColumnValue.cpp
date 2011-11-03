/*
 * =====================================================================================
 *
 *       Filename:  TestMatrixRowColumnValue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-3 13:09:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cassert>
#include <climits>
#include "common/Matrix.hpp"

#include "common/test/TestFunction.hpp"

using namespace my_gl;

void test()
{

     Matrix2 mat2;
     for(int i=0;i<Matrix2::LENGTH;++i)
     {
	  for (int j=0; j<Matrix2::LENGTH; ++j)
	  {
	       mat2(i,j)=myRand()/float(INT_MAX/20000);
	  }
     }

     float calced=rowColumnExprValue(mat2);

     float shouldBe=mat2(0,0)*mat2(1,1)-mat2(1,0)*mat2(0,1);
     assertEqual(calced,shouldBe);
}

int main(int argc, const char *argv[])
{


     for (int i=0; i<400; ++i)
     {
	  test();
     }
     
	
	return 0;
}
