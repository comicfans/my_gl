/*
 * =====================================================================================
 *
 *       Filename:  OpenCLLineRasterizer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/3 13:00:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENCL_LINE_RASTERIZER_HPP

#define OPENCL_LINE_RASTERIZER_HPP

#include "soft_impl/pipeline/rasterizer/Rasterizer.hpp"
#include "opencl_impl/CLParameterBinder.hpp"

namespace my_gl {
     class OpenCLLineRasterizer :public Rasterizer,CLParameterBinder{
     public:
     	OpenCLLineRasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     OpenCLFragmentAttributeBuffer& fragmentAttributeBuffer,
		     OpenCLDepthBuffer& depthBuffer,
		     DepthRange& depthRange,
		     GLenum primitiveMode,
		     cl::Context& clContext);

	virtual void rasterize(
			 const ClippedPrimitiveGroup& clippedPrimitiveGroup);

	virtual int bindToKernel(cl::Kernel kernel,int idx) ;

     	virtual ~OpenCLLineRasterizer ();
     
     private:
     	/* data */
     };
	
} /* my_gl */


#endif /* end of include guard: OPENCL_LINE_RASTERIZER_HPP */
