/*
 * =====================================================================================
 *
 *       Filename:  TestRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-28 18:48:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cassert>
#include "Rasterizer.hpp"
#include "pipeline/clipper/PointClipper.hpp"
#include "common/test/TestFunction.hpp"
#include "common/Vec4.hpp"
#include "pipeline/interpolator/WindowCoordinatesInterpolator.hpp"
#include "shader/FragmentAttributeBuffer.hpp"

using namespace my_gl;

void testRoundNearest()
{

     assert(Rasterizer::roundNearest(3.0)==3);
     assert(Rasterizer::roundNearest(3.4)==3);
     assert(Rasterizer::roundNearest(3.5)==4);
     assert(Rasterizer::roundNearest(3.6)==4);
}

WindowCoordinatesInterpolator interpolator;

int width=300,
    height=200;

FragmentAttributeBuffer fragmentAttributeBuffer(width,height,1);

inline static Vec4 randVec()
{
     Vec4 ret;

     for (int i=0; i<Vec4::LENGTH; ++i)
     {
	  ret[i]=myRand();
     }

     return ret;
}
	       
ViewportParameter parameter{0,0,width,height};

class ViewportTest:public Rasterizer
{
     public: 
	  void check()
	  {


	       for (int i=0; i<1000; ++i)
	       {
		    Vec4 vec4=randVec();

		    if (PointClipper::inClipVolume(vec4))
		    {
			 auto winCoord=toWindowCoordinates(vec4/vec4.w());

			 assert(winCoord.first>=0 && winCoord.first<=height);
			 assert(winCoord.second>=0 && winCoord.second<=width);
		    }
		    
	       }
	  }

	  ViewportTest():
	       Rasterizer(parameter,interpolator,fragmentAttributeBuffer)
     {}
	       
	  virtual void elementRasterize
		    (ConstAttributeGroupRef* attributeGroupRefs){}


};

int main(int argc, const char *argv[])
{
     testRoundNearest();

     ViewportTest viewportTest;

     viewportTest.check();
	
}
