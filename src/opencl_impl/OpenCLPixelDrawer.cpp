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
#include <array>
#include <cassert>

#include <SDL/SDL.h>

#include "opencl_impl/CLSource.hpp"
#include "soft_impl/pipeline/ColorBuffer.hpp"

namespace my_gl {

     OpenCLPixelDrawer::OpenCLPixelDrawer(cl::Context& openCLContext)
	  :_openCLContext(openCLContext),_currentBindedFrameBuffer(nullptr)
     { 
	  std::vector<cl::Device> devices= 
	       _openCLContext.getInfo<CL_CONTEXT_DEVICES>();

	  assert(devices.size()||"no opencl device found");


	  cl::Device defaultDevice=devices[0];

	  std::vector<size_t> workItemSizes;

	  defaultDevice.getInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES,&workItemSizes);

	  assert(workItemSizes.size()>=2 || "device not support 2 dim ");

	  _maxHeight=workItemSizes[0];

	  _maxWidth=workItemSizes[1];

	  _commandQueue=cl::CommandQueue(_openCLContext,defaultDevice);

	  CLSource clSource("OpenCLPixelDrawer.cl");

	  cl::Program program(_openCLContext,clSource.getSources());

	  cl_int buildResult=program.build(devices);

	  assert(buildResult==CL_SUCCESS);

	  _expendKernel=cl::Kernel(program,"float4ToUchar4");

     }

     void OpenCLPixelDrawer::onInit(size_t width, size_t height)
     {

	  assert(width<= _maxWidth || "width not support");
	  assert(height<= _maxHeight|| "height not support");

	  _inputBufferSize=width*height*sizeof(float)*4;
	  _outputBufferSize=width*height*sizeof(uint32_t);

	  SDLPixelDrawer::onInit(width, height);

	  std::array<size_t,3> sizeList{height,width,4};
	  _outputUint32Buffer.resize(sizeList);

	  _outputCLBuffer=cl::Buffer(_openCLContext,
		    CL_MEM_WRITE_ONLY|CL_MEM_USE_HOST_PTR,
		    _outputBufferSize,
		    _outputUint32Buffer.data());

	  _ndRange=cl::NDRange(height,width);

	  _expendKernel.setArg(1,_outputCLBuffer);
     }

     OpenCLPixelDrawer::~OpenCLPixelDrawer()
     { }


     void OpenCLPixelDrawer::recreateInputBuffer()
     {

	  const void* pointer=
	       (&(_currentBindedFrameBuffer->operator()(0,0)));

	  size_t address=reinterpret_cast<size_t>(pointer);

	  assert((address %16==0)||
		    "vec address not align to 16 byte");

	  _inputCLBuffer=cl::Buffer(_openCLContext,
		    CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
		    _inputBufferSize,
		    const_cast<void*>(pointer));

	  _expendKernel.setArg(0,_inputCLBuffer);

     }

     void OpenCLPixelDrawer::onDraw(const ColorBuffer& frameBuffer)
     {
	  if ((_currentBindedFrameBuffer==nullptr )|| 
		    (&frameBuffer != _currentBindedFrameBuffer))
	  {
	       _currentBindedFrameBuffer=&frameBuffer;
	       recreateInputBuffer();
	  }

	  cl_int result=
	       _commandQueue.enqueueNDRangeKernel(
			 _expendKernel,
			 cl::NullRange,
			 _ndRange,
			 cl::NDRange(1,1));

	  assert(result==CL_SUCCESS || "execute opencl failed");

	  result=_commandQueue.finish();

	  assert(result==CL_SUCCESS || "execute opencl finish failed");

	  dropEvent();
     }

     void OpenCLPixelDrawer::onFlush()
     {
	  void *temp=
	       _commandQueue.enqueueMapBuffer(_outputCLBuffer,true,
			 CL_MAP_READ,0,_outputBufferSize);

	  SurfaceLocker locker(_screenPtr);

	  for (int y=0; y<height(); ++y)
	  {
	       for (int x=0; x<width(); ++x)
	       {
		    auto fourBytes=_outputUint32Buffer[y][x];

		    Uint32 packedValue=
			 SDL_MapRGB(_screenPtr->format,fourBytes[0]
				   ,fourBytes[1],fourBytes[2]);

		    //SDL surface origin is left-upper
		    //but opengl default frameBuffer origin is left-lower

		    Uint8 *p = (Uint8 *)_screenPtr ->pixels + 
			 (height()-y) * _screenPtr->pitch + 
			 x * _screenPtr->format->BytesPerPixel;

		    _setPixelFunc(p,packedValue);


	       }
	  }

	  _commandQueue.enqueueUnmapMemObject(_outputCLBuffer,temp);

	  SDLPixelDrawer::onFlush();

     }

} /* my_gl */
