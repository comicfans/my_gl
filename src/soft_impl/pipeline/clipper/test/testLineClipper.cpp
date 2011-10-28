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

#include <cstdlib>
#include <cmath>

#include "LineClipper.hpp"
#include "PointClipper.hpp"

#include "common/test/TestFunction.hpp"

#include "pipeline/interpolator/Interpolator.hpp"

using namespace my_gl;
using std::rand;
using std::abs;
using std::fmod;

void static testAllIn()
{
     Vec4 p1(1,1,1,1),
	  p2(3,2,3,4);

     auto percent =LineClipper::parallelClip
	  (p1, p2, LineClipper::ClipDim::X);

     assert(!LineClipper::outOfClipVolume(percent));

     assertEqual(percent.first,0);
     assertEqual(percent.second,1);

}

static int myRand()
{
     int ret=rand();

     ret-=RAND_MAX/2;

     return ret;
}

void static testClipLogic()
{
     Vec4 p1,p2;
     p1[3]=myRand();
     p2[3]=myRand();
     for(int i=0;i<3;++i)
     {
	  int sign=(abs(myRand())%2==0?1:-1);
	  p1[i]=fmod(myRand(),abs(p1.w()))*sign;
	  p2[i]=myRand();
     }

     LineClipper::ClipPercent finalResult={0,1};
     for (int i=0; i<3; ++i)
     {
	  auto clipPercent=LineClipper::parallelClip(p1,p2,
		    LineClipper::ClipDim(i));
	  assert(clipPercent.first>=0);
	  assert(clipPercent.second<=1);
	  assert(clipPercent.first<=clipPercent.second);

	  assertEqual(clipPercent.first,0);

	  finalResult=LineClipper::mergePercent(finalResult,clipPercent);
     }


     if (!PointClipper::inClipVolume(p2))
     {
	  assert(finalResult.second<1);
     
	  Vec4 clipPoint;

	  Interpolator::calculate(p1,p2,finalResult.second,clipPoint);

	  bool atLeastEqual=false;

	  for(int i=0;i<3;++i)
	  {
	       atLeastEqual=equal(abs(clipPoint[i]),abs(clipPoint.w()));
	       if (atLeastEqual)
	       {
		    return;
	       }
	  }

	  assert(false);
     }

}

void static testClipValue()
{
     Vec4 p1(0,0,0.5,1.5),
	  p2(1,0,-4,0);

     auto clipPercent=LineClipper::parallelClip
	  (p1,p2,LineClipper::ClipDim::Z);


     Vec4 result;

     Interpolator::calculate(p1, p2, 
	       clipPercent.second, result);

     assert(equal(result,Vec4(1.0/3,0,-1,1)));


}

int main(int argc, const char *argv[])
{
     testClipValue();
	
     testAllIn();

     for (int i=0; i<1000; ++i)
     {
	  testClipLogic();
     }
     
}
