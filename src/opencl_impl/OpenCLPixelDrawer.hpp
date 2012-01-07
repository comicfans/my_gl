/*
 * =====================================================================================
 *
 *       Filename:  OpenCLPixelDrawer.hpp
 *
 *    Description:  use OpenCL to expand float to RGB
 *
 *        Version:  1.0
 *        Created:  2012-1-7 19:03:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENCL_PIXEL_DRAWER_HPP

#define OPENCL_PIXEL_DRAWER_HPP

#include <CL/cl.hpp>

#include "soft_impl/SDLPixelDrawer.hpp"

namespace my_gl {

     class OpenCLPixelDrawer :public SDLPixelDrawer{
     public:

     	OpenCLPixelDrawer (cl::Context& openCLContext);

	virtual void onDraw(const ColorBuffer& frameBuffer);

	virtual void onInit(size_t width,size_t height);

     	virtual ~OpenCLPixelDrawer ();
     
     private:

	cl::Context  _openCLContext;
	cl::Kernel _expendKernel;
	cl::CommandQueue _commandQueue;
     };
	
} /* my_gl */



#endif /* end of include guard: OPENCL_PIXEL_DRAWER_HPP */
