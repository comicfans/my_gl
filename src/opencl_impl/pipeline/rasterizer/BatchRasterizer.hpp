/*
 * =====================================================================================
 *
 *       Filename:  BatchRasterizer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-18 15:29:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BATCH_RASTERIZER_HPP

#define BATCH_RASTERIZER_HPP

#include <CL/cl.hpp>

#include "Enum.hpp"
#include "soft_impl/pipeline/rasterizer/Rasterizer.hpp"
#include "opencl_impl/CLParameterBinder.hpp"

namespace my_gl {

     class OpenCLFragmentAttributeBuffer;
     class OpenCLDepthBuffer;

     class BatchRasterizer :public Rasterizer,protected CLParameterBinder{
	  public:
	       BatchRasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     OpenCLFragmentAttributeBuffer& fragmentAttributeBuffer,
		     OpenCLDepthBuffer& depthBuffer,
		     DepthRange& depthRange,
		     PrimitiveMode primitiveMode,
		     cl::Context& clContext);

	       virtual void rasterize(
			 const ClippedPrimitiveGroup& clippedPrimitiveGroup);

	       virtual int bindToKernel(cl::Kernel kernel,int idx) override;

	  protected:

	       const PrimitiveMode _primitiveMode;
	       cl::Context& _CLContext;
	       cl::CommandQueue _commandQueue;
	       cl::Kernel _kernel;
	       cl::Buffer _fragmentAttibuteCLBuffer;
	       cl::Buffer _depthBufferCLBuffer;

     };

} /* my_gl */


#endif /* end of include guard: BATCH_RASTERIZER_HPP */
