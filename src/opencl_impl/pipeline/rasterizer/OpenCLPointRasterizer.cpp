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

	  err=program.build(devices,"-g -O0");

	  assert(err==CL_SUCCESS || "program build failed");

	  static const char* KERNEL_NAMES[]={
	       "rasterizePointsWithEarlyZ",
	       "rasterizeLines",
	       "rasterizeTriangles"};

	  _kernel=cl::Kernel(program,
		    KERNEL_NAMES[int(_primitiveMode)],&err);

	  assert(err==CL_SUCCESS || "kernel create failed");

	  //bind FragmentAttributeBuffer
	  size_t fragmentAttributeBufferSize=fragmentAttributeBuffer.width() * 
	       fragmentAttributeBuffer.height()* 
	       fragmentAttributeBuffer.attributeNumber() *
	       sizeof(Vec4);

	  _fragmentAttibuteCLBuffer=cl::Buffer(_CLContext,
		    CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
		    fragmentAttributeBufferSize,
		    fragmentAttributeBuffer.getRawData());

	  //magic need refactor?
	  int idx=7;
	  _kernel.setArg(idx++,_fragmentAttibuteCLBuffer);

	  //bind DepthBuffer
	  
	  size_t depthBufferSize=depthBuffer.width()
	       *depthBuffer.height()*sizeof(float);

	  _depthBufferCLBuffer=cl::Buffer(_CLContext,
		    CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
		    depthBufferSize,depthBuffer.getRawData());
	  _kernel.setArg(idx++,_depthBufferCLBuffer);
	  //bind widthHeight


	  struct {
	       uint32_t width;
	       uint32_t height;
	  } widthHeight{uint32_t(depthBuffer.width()),uint32_t(depthBuffer.height())};

	  _kernel.setArg(idx++,widthHeight);

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

	  paramIdx=openCLClippedPrimitiveGroup.
	       bindToKernel(_kernel, paramIdx);

	  bindToKernel(_kernel,paramIdx);

	  cl::NDRange globalNDRange(clippedPrimitiveGroup.elementNumber());

	  _commandQueue.enqueueNDRangeKernel
	       (_kernel,cl::NDRange(),globalNDRange, cl::NDRange(1));

	  _commandQueue.finish();
	  
     }

     int OpenCLPointRasterizer::bindToKernel(cl::Kernel kernel,int idx)
     {

	  kernel.setArg(idx++,ViewportParameter(_viewportParameter));

	  struct 
	  {
	       float nearValue;
	       float farValue;
	       float diff;
	  } floatDepthRange{(float)_depthRange.nearValue,
	       (float)_depthRange.farValue,(float)_depthRange.diff};

	  kernel.setArg(idx++,floatDepthRange);

	  return idx;
     }

	
} /* my_gl */

