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
#include "DepthRange.hpp"
#include "pipeline/clipper/PointClipper.hpp"
#include "pipeline/DepthBuffer.hpp"
#include "common/test/TestFunction.hpp"
#include "common/Vec.hpp"
#include "pipeline/interpolator/WinCoordInterpolator.hpp"
#include "shader/FragmentAttributeBuffer.hpp"

using namespace my_gl;

void testRoundNearest()
{

     assert(Rasterizer::roundNearest(3.0)==3);
     assert(Rasterizer::roundNearest(3.4)==3);
     assert(Rasterizer::roundNearest(3.5)==4);
     assert(Rasterizer::roundNearest(3.6)==4);
}

WinCoordInterpolator interpolator;

int width=300,
    height=200;

FragmentAttributeBuffer fragmentAttributeBuffer(width,height,1);

DepthRange depthRange;

DepthBuffer depthBuffer(width,height);

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
			 auto winCoord=toWinCoord(vec4/vec4.w());

			 assert(winCoord.y()>=0 && winCoord.y()<=height);
			 assert(winCoord.x()>=0 && winCoord.x()<=width);
		    }
		    
	       }
	  }

	  ViewportTest():
	       Rasterizer(parameter,interpolator,fragmentAttributeBuffer,depthBuffer,depthRange)
     {}
	       
	  virtual void elementRasterize
		    (const ConstAttributeGroupRefList &attributeGroupRefs){}


};

int main(int argc, const char *argv[])
{
     testRoundNearest();

     ViewportTest viewportTest;

     viewportTest.check();
	
}
