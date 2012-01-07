/*
 * =====================================================================================
 *
 *       Filename:  OpenCLPixelDrawer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-7 19:16:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLPixelDrawer.hpp"

#include <vector>
#include <cassert>

namespace my_gl {

     OpenCLPixelDrawer::OpenCLPixelDrawer(cl::Context& openCLContext)
	  :_openCLContext(openCLContext)
     {  }

     void OpenCLPixelDrawer::onInit(size_t width, size_t height)
     {
	  SDLPixelDrawer::onInit(width, height);

	  std::vector<cl::Device> devices= 
	       _openCLContext.getInfo<CL_CONTEXT_DEVICES>();

	  assert(devices.size()||"no opencl device found");

	  _commandQueue=cl::CommandQueue(_openCLContext,devices[0]);

     }

     OpenCLPixelDrawer::~OpenCLPixelDrawer()
     { }


	
} /* my_gl */
