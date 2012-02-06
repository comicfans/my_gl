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

     class BatchRasterizer :public Rasterizer,protected CLParameterBinder{
	  public:
	       BatchRasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange,
		     PrimitiveMode primitiveMode,
		     cl::Context& clContext);

	       virtual void rasterize(
			 const ClippedPrimitiveGroup& clippedPrimitiveGroup);


	  protected:
	       const PrimitiveMode _primitiveMode;
	       cl::Context& _CLContext;
	       cl::CommandQueue _commandQueue;
	       cl::Kernel _kernel;
	       cl::Buffer _fragmentAttibuteCLBuffer;

	  private:
	       virtual void bindToKernel(cl::Kernel kernel) override;
     };

} /* my_gl */


#endif /* end of include guard: BATCH_RASTERIZER_HPP */
