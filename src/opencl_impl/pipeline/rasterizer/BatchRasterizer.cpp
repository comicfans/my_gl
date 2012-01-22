/*
 * =====================================================================================
 *
 *       Filename:  BatchRasterizer.cpp
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

#include "BatchRasterizer.hpp"


#include <cassert>
#include <vector>

#include "opencl_impl/CLSource.hpp"


namespace my_gl {

     BatchRasterizer::BatchRasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange,
		     PrimitiveMode primitiveMode,
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

	  cl_int err=CL_SUCCESS;

	  err=program.build(devices);

	  assert(err==CL_SUCCESS || "program build failed");

	  static const char* KERNEL_NAMES[]={
	       "rasterizePoints",
	       "rasterizeLines",
	       "rasterizeTriangles"};

	  _kernel=cl::Kernel(program,
		    KERNEL_NAMES[int(_primitiveMode)],&err);

	  assert(err==CL_SUCCESS || "kernel create failed");

	  size_t bufferSize=fragmentAttributeBuffer.width() * 
	       fragmentAttributeBuffer.height()* 
	       fragmentAttributeBuffer.attributeNumber() *
	       sizeof(Vec4);



	  _fragmentAttibuteCLBuffer=cl::Buffer(_CLContext,
		    CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
		    _inputBufferSize,
		    const_cast<void*>(pointer));


     }


	  
     void BatchRasterizer::rasterize(const 
	       ClippedPrimitiveGroup& clippedPrimitiveGroup)
     {

	  
     }


	
} /* my_gl */

