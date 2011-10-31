/*
 * =====================================================================================
 *
 *       Filename:  TestLineRasterizer.cpp
 *
 *    Description:  test if line rasterizer worked
 *
 *        Version:  1.0
 *        Created:  2011-10-28 20:02:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <functional>
#include <cstdlib>
#include <algorithm>
#include <cmath>

#include <SDL.h>

#include "pipeline/interpolator/WinCoordInterpolator.hpp"
#include "pipeline/rasterizer/SimpleLineRasterizer.hpp"
#include "shader/FragmentAttributeBuffer.hpp"
#include "pipeline/FrameBuffer.hpp"
#include "SDLPixelDrawer.hpp"
#include "pipeline/rasterizer/LineInfo.hpp"

using std::bind;
using std::placeholders::_1;
using std::rand;
using std::fill_n;
using std::minmax;

using namespace my_gl;
WinCoordInterpolator interpolator;

int width=300,
    height=200;

FragmentAttributeBuffer fragmentAttributeBuffer(width,height,1);

ViewportParameter parameter{0,0,width,height};

FrameBuffer frameBuffer(width,height);

SDLPixelDrawer pixelDrawer;

class TestSimpleLineRasterizer:public  SimpleLineRasterizer
{
     public:
	  
	  TestSimpleLineRasterizer()
	       :SimpleLineRasterizer
		(parameter,interpolator,fragmentAttributeBuffer)
     {}

	  static WinCoord randWinCoord()
	  {
		    int randX=rand()%width,
			randY=rand()%height;

		    return {randY,randX};
	  }

	  static void writePixel(const WinCoord& winCoord,
		    const WinCoord& beg,const WinCoord& end)
	  {

	       auto minMaxFirst=minmax(beg.first,end.first);

	       assert(winCoord.first>=minMaxFirst.first && 
			 winCoord.first<=minMaxFirst.second);

	       auto minMaxSecond=minmax(beg.second,end.second);

	       assert(winCoord.second>=minMaxSecond.first && 
			 winCoord.second<=minMaxSecond.second);

	       Vec4& rgba=frameBuffer(winCoord);

	       fill_n(rgba.values(),3,0.5);
	  }

	  void test()
	  {

	       for (int i=0; i<100; ++i)
	       {
		    auto winCoord1=randWinCoord(),
			 winCoord2=randWinCoord();

		    LineInfo lineInfo(winCoord1,winCoord2);

		    if (lineInfo.parallelToAxis() || 
			      lineInfo.isOnlyPoint())
		    {
			 break;
		    }

		    rasterize(winCoord1,winCoord2,lineInfo,
			      bind(writePixel,_1,winCoord1,winCoord2));

		    pixelDrawer.onDraw(frameBuffer);

		    pixelDrawer.onFlush();
		    SDL_Delay(10);

	       }

	  }
};

extern "C"
{
int main(int argc, char **)
{
     pixelDrawer.onInit(width,height);

     TestSimpleLineRasterizer test;

     test.test();

     return 0;
}
}
