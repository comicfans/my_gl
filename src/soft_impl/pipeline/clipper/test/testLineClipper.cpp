/*
 * =====================================================================================
 *
 *       Filename:  testLineClipper.cpp
 *
 *    Description:  test Liang-Barsky clipp algorithm
 *
 *        Version:  1.0
 *        Created:  2011/10/14 8:42:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "LineClipper.hpp"

#include "common/test/TestFunction.hpp"

#include "pipeline/interpolator/Interpolator.hpp"

using namespace my_gl;

void static testAllIn()
{
     Vec4 p1(1,1,1,1),
	  p2(3,2,3,4);

     auto percent =LineClipper::parallelClip
	  (p1, p2, LineClipper::ClipDim::X);

     assert(!LineClipper::outOfClipVolume(percent));

     assert(percent.first<=0);
     assert(percent.second>=1);

}

void static testClip()
{
     Vec4 p1(0,0,0.5,1.5),
	  p2(1,0,-4,0);

     auto clipPercent=LineClipper::parallelClip(p1,p2,LineClipper::ClipDim::Z);


     Vec4 result;

     Interpolator::calculate(p1, p2, 
	       clipPercent.second, result);

     assert(equal(result,Vec4(1.0/3,0,-1,1)));


}

int main(int argc, const char *argv[])
{
     testClip();
	
     testAllIn();
}
