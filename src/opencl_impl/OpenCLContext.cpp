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
#include "soft_impl/shader/FragmentShader.hpp"
#include "soft_impl/pipeline/ColorBuffer.hpp"

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
			VertexAttributeBuffer::DEFAULT_OUT_SIZE,*_CLContext));

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

     void OpenCLContext::fragmentShaderStage(GLenum catalog)
     {
	  //read from opencl buffer need map action,
	  //a temp hack
	  if (catalog!=GL_POINTS)
	  {
	       SoftContext::fragmentShaderStage(catalog);
	       return;
	  }

	  OpenCLPointRasterizer* rasterizer=static_cast<OpenCLPointRasterizer*>
	       (_rasterizers.find(GL_POINTS)->second);


	  OpenCLFragmentAttributeBuffer& fragmentAttributeBuffer=
	       static_cast<OpenCLFragmentAttributeBuffer&>(*_fragmentAttributeBufferPtr);

	  Vec4 *temp;
	  //currently use CL_MEM_USE_HOST_PTR to do fragmentAttributeBuffer
	  //so only lock is needed, mapped ptr is the same as host ptr
	  //when full opencl pipeline is supported ,need refactor here

	  temp=static_cast<Vec4*>(fragmentAttributeBuffer.beginRead
		    (rasterizer->getCommandQueue()));



	  auto activeFragWinCoords=_fragmentAttributeBufferPtr
	       ->getActiveFragWinCoords();

	  _fragmentShaderPtr->setTextureObject
	       (_textureObjectManager.getActiveTextureObject());



	  int attributeNumber=_clippedPrimitiveGroupPtr->attributeNumber();

	  for(auto &winCoord:activeFragWinCoords)
	  {
	       _fragmentShaderPtr->shade(
			 temp+(winCoord.y()*_width+winCoord.x())*attributeNumber,
				     getFrameBuffer<ColorBuffer>()(winCoord)
			 );
	  }

	  fragmentAttributeBuffer.endRead(rasterizer->getCommandQueue(),temp);

     }

} /* my_gl */
