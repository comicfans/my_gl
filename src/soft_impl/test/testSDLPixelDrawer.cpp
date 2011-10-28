/*
 * =====================================================================================
 *
 *       Filename:  testSDLPixelDrawer.cpp
 *
 *    Description:  test if sdl pixel drawer is work
 *
 *        Version:  1.0
 *        Created:  2011-10-28 0:50:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cmath>

#include "SDLPixelDrawer.hpp"
#include "pipeline/FrameBuffer.hpp"

using std::min;
using namespace my_gl;

int main(int argc, const char *argv[])
{

     FrameBuffer frameBuffer(400,300);

     int minValue=min(frameBuffer.height(),frameBuffer.width());

     for (int i=0; i<minValue; ++i)
     {
	  Vec4& aPoint=frameBuffer(i,i);

	  aPoint[0]=0.5;
	  aPoint[1]=0.5;
	  aPoint[2]=0.5;

     }

     SDLPixelDrawer drawer;

     PixelDrawer &ref=drawer;

     ref.onInit(400,300);

     for (int i=0; i<10; ++i)
     {
	  ref.onDraw(frameBuffer);
	  ref.onFlush();
     }

     return 0;
}
