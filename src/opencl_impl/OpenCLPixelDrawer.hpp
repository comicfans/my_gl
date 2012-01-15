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

#include <boost/multi_array.hpp>

#include <CL/cl.hpp>

#include "soft_impl/SDLPixelDrawer.hpp"

namespace my_gl {

     class OpenCLPixelDrawer :public SDLPixelDrawer{
     public:

     	OpenCLPixelDrawer (cl::Context& openCLContext);

	virtual void onDraw(const ColorBuffer& frameBuffer);

	virtual void onFlush();

	virtual void onInit(size_t width,size_t height);

     	virtual ~OpenCLPixelDrawer ();
     
     private:

	/** 
	 * @brief if color frame buffer is different from prev call
	 * 		recreate opencl input buffer from it
	 * 		or input buffer will not change during life time
	 * 
	 */
	void recreateInputBuffer();

	cl::Context  _openCLContext;
	cl::Kernel _expendKernel;
	cl::CommandQueue _commandQueue;
	cl::Buffer _inputCLBuffer;
	cl::Buffer _outputCLBuffer;
	cl::NDRange _ndRange;

	int _maxHeight;
	int _maxWidth;

	boost::multi_array<uint8_t, 3> _outputUint32Buffer;

	size_t _inputBufferSize;
	size_t _outputBufferSize;

	ColorBuffer const *_currentBindedFrameBuffer;
     };
	
} /* my_gl */



#endif /* end of include guard: OPENCL_PIXEL_DRAWER_HPP */
