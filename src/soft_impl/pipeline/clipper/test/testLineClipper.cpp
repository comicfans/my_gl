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

int main(int argc, const char *argv[])
{
     Vec4 p1(0,0,0.5,1.5),
	  p2(1,0,-4,0);

     float percent=LineClipper::
	  clipInHomogenousCoordinates(p1, p2, 
	       LineClipper::ClipDim::Z, LineClipper::ClipSide::MIN);


     Vec4 result;

     Interpolator::calculate(p1, p2, percent, result);

     assert(equal(result,Vec4(1.0/3,0,-1,1)));

	
}
