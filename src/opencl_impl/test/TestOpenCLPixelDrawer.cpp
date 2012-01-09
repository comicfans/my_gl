/*
 * =====================================================================================
 *
 *       Filename:  TestOpenCLPixelDrawer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-9 0:03:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "opencl_impl/OpenCLPixelDrawer.hpp"
#include "soft_impl/pipeline/ColorBuffer.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{

     cl::Context context(CL_DEVICE_TYPE_DEFAULT);

     OpenCLPixelDrawer drawer(context);

     const int width=400,height=300;

     drawer.onInit(width,height);

     while (true)
     {

	  ColorBuffer colorBuffer(width,height);

	  for (int y=0; y<height; ++y)
	  {
	       for (int x=0; x<width; ++x)
	       {
		    colorBuffer(x,y)[0]=0;
		    colorBuffer(x,y)[1]=float(y)/height;
		    colorBuffer(x,y)[2]=float(x)/width;
	       }
	  }

	  drawer.onDraw(colorBuffer);

	  drawer.onFlush();
     }


     return 0;
}

