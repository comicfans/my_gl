/*
 * =====================================================================================
 *
 *       Filename:  TestMatrixVecMul.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-3 14:05:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "common/Matrix.hpp"
#include "common/Vec.hpp"
#include "common/test/TestFunction.hpp"

using namespace my_gl;

static void test()
{
     Matrix4 identity=Matrix4::identity();

     Vec4 vec=randVec();

     vec[3]=1;

     assertEqual(vec,identity*vec);

     float x=3,y=234,z=643;

     Matrix4 translateMat=translate(x,y,z);

     Vec4 translatedVec=translateMat*vec;

     Vec4 diff=translatedVec-vec;

     assertEqual(diff,Vec4{x,y,z,0});


}

int main(int argc, const char *argv[])
{
	
     test();
	return 0;
}
