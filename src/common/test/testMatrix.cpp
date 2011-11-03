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

#include <cassert>
#include <algorithm>
#include "common/Matrix.hpp"

#include "TestFunction.hpp"

using std::generate_n;

using namespace my_gl;

void testAssign()
{
     float values16[Matrix4::ELEMENTS_NUMBER];

     generate_n(values16,Matrix4::ELEMENTS_NUMBER,myRand);

     Matrix4 mat;

     for (int column=0; column<Matrix4::LENGTH; ++column)
     {
	  for (int row=0; row<Matrix4::LENGTH; ++row)
	  {
	       mat(column,row)=values16[column*Matrix4::LENGTH+row];
	  }
     }
     
     bool same=std::equal(values16,values16+Matrix4::ELEMENTS_NUMBER,mat.values());

     assert(same);
}

int main(int argc, const char *argv[])
{

     for (int i=0; i<300; ++i)
     {
	  testAssign();
     }

}
