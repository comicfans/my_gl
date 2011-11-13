/*
 * =====================================================================================
 *
 *       Filename:  TestVecNormalize.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-13 20:30:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <cmath>

#include "common/Vec.hpp"
#include "common/test/TestFunction.hpp"

using namespace my_gl;
using std::sqrt;

void test()
{
     Vec3 randVec;
     randVec[0]=myRand();
     randVec[1]=myRand();
     randVec[2]=myRand();

     normalize(randVec);

     assertEqual(length(randVec),1);

}

void testSpecial()
{
     Vec3 toNormalize1={1,0,0};
     normalize(toNormalize1);
     assertEqual(length(toNormalize1),1);


     Vec3 toNormalize={1,1,1};

     normalize(toNormalize);

     float shouldBe=1.0/sqrt(3);

     assertEqual(toNormalize.x(),shouldBe);
     assertEqual(toNormalize.y(),shouldBe);
     assertEqual(toNormalize.z(),shouldBe);

     assertEqual(length(toNormalize),1);


}

int main(int argc, const char *argv[])
{
	
     testSpecial();

     for (int i=0; i<300; ++i)
     {
	  test();
     }
     
	
}
