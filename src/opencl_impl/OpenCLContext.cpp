/*
 * =====================================================================================
 *
 *       Filename:  OpenCLContext.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-5 16:12:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *        Company:
 *
 * =====================================================================================
 */

#include "OpenCLContext.hpp"

#include <CL/cl.hpp>

#include "soft_impl/pipeline/clipper/Clipper.hpp"

#include "opencl_impl/OpenCLPixelDrawer.hpp"
#include "opencl_impl/pipeline/OpenCLClippedPrimitiveGroup.hpp"
#include "opencl_impl/shader/OpenCLFragmentAttributeBuffer.hpp"
#include "opencl_impl/pipeline/rasterizer/OpenCLPointRasterizer.hpp"

#include "opencl_impl/pipeline/OpenCLDepthBuffer.hpp"

using std::vector;

namespace my_gl {


     OpenCLContext::OpenCLContext (size_t width,size_t height)
	  :SoftContext(width,height)
     {
         initOpenCL();

	 //TODO need clean
         SoftContext::_pixelDrawerPtr.reset(
                     new OpenCLPixelDrawer(*_CLContext.get()));

	 //use OpenCLFragmentAttributeBuffer
	 SoftContext::_fragmentAttributeBufferPtr.reset(
		   new OpenCLFragmentAttributeBuffer(width,height,
			VertexAttributeBuffer::DEFAULT_OUT_SIZE));

	  _allFrameBuffer.replace(DepthBuffer::ORDER_INDEX,
		    new OpenCLDepthBuffer(width,height));



	 _pixelDrawerPtr->onInit(width,height);

	 //set rasterizer
	 for(auto primitiveMode : {GL_POINTS
		   //,GL_LINES,GL_TRIANGLES
		   })
	 {

	      auto it =_rasterizers.find(primitiveMode);

	      assert(it!=_rasterizers.end());

	      _rasterizers.replace(it,
			new OpenCLPointRasterizer(_viewportParameter,
			     *_interpolatorPtr,

			     static_cast<OpenCLFragmentAttributeBuffer&>
			     (*_fragmentAttributeBufferPtr),

			     static_cast<OpenCLDepthBuffer&>
			     (getFrameBuffer<DepthBuffer>()),

			     _depthRange,
			     primitiveMode,*_CLContext));

	 }

         Context::setInstance(this);
     }

     OpenCLContext::~OpenCLContext()
     {}


     void OpenCLContext::initOpenCL()
     {

	  _CLContext.reset(new cl::Context(CL_DEVICE_TYPE_DEFAULT));
     }

     void OpenCLContext::clipPrimitive(
	       const my_gl::PrimitiveIndex &primitiveIndex, 
	       GLenum catalog)
     {
	  //TODO copy & paste from super function ,need refactor
	  //choose right clipper
	  Clipper& clipper=*(_clippers.find(catalog)->second);

	  //reset ClippedPrimitiveGroup

	  _clippedPrimitiveGroupPtr.reset(
		    new OpenCLClippedPrimitiveGroup
		    (_vertexAttributeBuffer,
		     primitiveIndex.primitiveMode()));

	  clipper.clip(_vertexAttributeBuffer,
		    primitiveIndex,*_clippedPrimitiveGroupPtr);


     }


} /* my_gl */
