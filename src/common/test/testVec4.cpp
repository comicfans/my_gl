/*
 * =====================================================================================
 *
 *       Filename:  testVec4.cpp
 *
 *    Description:  test basic operator of Vec4
 *
 *        Version:  1.0
 *        Created:  2011-10-26 12:09:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cassert>

#include "common/Vec.hpp"
#include "common/test/TestFunction.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     Vec4 p1{1,2,3,4},
	  p2{1,2,3,4};

     Vec4 zero=p1-p2;
     
     assert(equal(zero,Vec4{0,0,0,0}));

     assert(equal(p1*3,Vec4{3,6,9,12}));

     assert(equal(p2*0.5,Vec4{
			 p2.x()*0.5f,
			 p2.y()*0.5f,
			 p2.z()*0.5f,
			 p2.w()*0.5f}));

     Vec4 mul=p2;

     float percent=0.345;
     mul*=percent;

     assert(equal(mul,p2*percent));
	
}
