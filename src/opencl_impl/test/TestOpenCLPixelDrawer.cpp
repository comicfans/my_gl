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


#include <vector>
#include "opencl_impl/OpenCLPixelDrawer.hpp"
#include "soft_impl/pipeline/ColorBuffer.hpp"


using namespace my_gl;

int main(int argc, const char *argv[])
{

     std::vector<cl::Platform> platforms;

     cl::Platform::get(& platforms);

     assert(platforms.size() || "no Platform found");

     cl_context_properties properties[] = 
     { CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};

     cl::Context context(CL_DEVICE_TYPE_CPU,properties);



     OpenCLPixelDrawer drawer(context);

     const int width=512,height=512;

     drawer.onInit(width,height);

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

     while (true)
     {

	  drawer.onDraw(colorBuffer);

	  drawer.onFlush();
     }


     return 0;
}

