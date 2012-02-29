/*
 * =====================================================================================
 *
 *       Filename:  OpenCLPointRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-18 17:21:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLPointRasterizer.hpp"


#include <cassert>
#include <cfloat>
#include <vector>

#include "opencl_impl/CLSource.hpp"
#include "opencl_impl/pipeline/OpenCLClippedPrimitiveGroup.hpp"

#include "opencl_impl/shader/OpenCLFragmentAttributeBuffer.hpp"
#include "opencl_impl/pipeline/OpenCLDepthBuffer.hpp"

#include "soft_impl/DepthRange.hpp"

namespace my_gl {

     OpenCLPointRasterizer::OpenCLPointRasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     OpenCLFragmentAttributeBuffer& fragmentAttributeBuffer,
		     OpenCLDepthBuffer& depthBuffer,
		     DepthRange& depthRange,
		     GLenum primitiveMode,
		     cl::Context& clContext)
		    :Rasterizer(viewportParameter,
			      interpolator,fragmentAttributeBuffer,
			      depthBuffer,depthRange),
			    _primitiveMode(primitiveMode),
			    _CLContext(clContext)
     {
	  CLSource clSource("BatchRasterizer.cl");


	  cl::Program program
	       (_CLContext,clSource.getSources());

	  std::vector<cl::Device> devices= 
	       _CLContext.getInfo<CL_CONTEXT_DEVICES>();

	  _commandQueue=cl::CommandQueue(clContext,devices[0]);

	  cl_int err=CL_SUCCESS;

	  //opencl function is selected at preprocess stage
	  static const char* OPTIONS=
#ifndef NDEBUG
	       "-g -O0"
#else
	       "-DNDEBUG"
#endif
	       ;

	  err=program.build(devices,OPTIONS);

	  assert(err==CL_SUCCESS || "program build failed");

	  static const char* KERNEL_NAMES[]={
	       "rasterizePoints",
	       "rasterizeLines",
	       "rasterizeTriangles"};

	  _kernel=cl::Kernel(program,
		    KERNEL_NAMES[int(_primitiveMode)],&err);

	  assert(err==CL_SUCCESS || "kernel create failed");



     }

     OpenCLPointRasterizer::~OpenCLPointRasterizer()
     {}

	  

     void OpenCLPointRasterizer::rasterize(const 
	       ClippedPrimitiveGroup& clippedPrimitiveGroup)
     {

	  const OpenCLClippedPrimitiveGroup& temp
	       =static_cast<const OpenCLClippedPrimitiveGroup&>(clippedPrimitiveGroup);

	  OpenCLClippedPrimitiveGroup& openCLClippedPrimitiveGroup
	       =const_cast<OpenCLClippedPrimitiveGroup&>(temp);

	  int paramIdx=0;

	  //bind clippedPrimitiveGroup
	  paramIdx=openCLClippedPrimitiveGroup.
	       bindToKernel(_kernel, paramIdx);

	  paramIdx=bindToKernel(_kernel,paramIdx);

	  //bind fragmentAttributeBuffer
	  int elementNumber=clippedPrimitiveGroup.elementNumber();
 
	  OpenCLFragmentAttributeBuffer& fragmentAttributeBuffer=
	       static_cast<OpenCLFragmentAttributeBuffer&>(Rasterizer::_fragmentAttributeBuffer);

	  fragmentAttributeBuffer.setActiveFragCoordsNumber(elementNumber);

	  paramIdx=fragmentAttributeBuffer.bindToKernel(_kernel,paramIdx);
	       

	  //enqueueNDRangeKernel

	  cl::NDRange globalNDRange(clippedPrimitiveGroup.elementNumber());

	  _commandQueue.enqueueNDRangeKernel
	       (_kernel,cl::NDRange(),globalNDRange, cl::NDRange(1));

	  _commandQueue.finish();
	 	  
	  //insert processed point into active fragments;
	  //
	  fragmentAttributeBuffer.storeActiveFragCoords(_commandQueue);

  
     }


		    
 struct WidthHeight{
		    cl_int width;
		    cl_int height;
	       };


	       struct  FloatDepthRange
	       {
		    float nearValue;
		    float farValue;
		    float diff;
	       };

	       struct PackedParam{
		    ViewportParameter viewportParameter;
		    FloatDepthRange depthRange;
		    WidthHeight widthHeight;
	       };

       int OpenCLPointRasterizer::bindToKernel(cl::Kernel kernel,int idx)
     {

	  PackedParam packedParam{
	       _viewportParameter,

		    FloatDepthRange{
		    float(_depthRange.nearValue),
		    float(_depthRange.farValue),
		    float(_depthRange.diff)
		    },

		    WidthHeight{
		    _depthBuffer.width(),
		    _depthBuffer.height()
		    }
	  };

	  kernel.setArg(idx++,packedParam);

	  //bind depthBuffer

	  OpenCLDepthBuffer& depthBuffer=static_cast<OpenCLDepthBuffer&>(_depthBuffer);
	  
	  depthBuffer.orderClear();
	  
	  //TODO only draw by order is supported , depth test :TBD
	  //
	  //draw by order need depth buffer to be act as atomic order counter
	  //so must clear it as -INT_MAX


	  size_t depthBufferSize=depthBuffer.width()
	       *depthBuffer.height()*sizeof(float);

	  _depthBufferCLBuffer=cl::Buffer(_CLContext,
		    CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
		    depthBufferSize,depthBuffer.getRawData());

	  _kernel.setArg(idx++,_depthBufferCLBuffer);


	  return idx;
     }

     cl::CommandQueue OpenCLPointRasterizer::getCommandQueue()
     {
	  return _commandQueue;
     }
	
} /* my_gl */

