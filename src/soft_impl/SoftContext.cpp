/*
 * =====================================================================================
 *
 *       Filename:  SoftContext.cpp
 *
 *    Description:  implementation of SoftContext
 *
 *        Version:  1.0
 *        Created:  2011-9-15 12:56:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SoftContext.hpp"

#include <climits>

#include "attribute_manager/NormalManager.hpp"
#include "attribute_manager/ColorManager.hpp"
#include "attribute_manager/VertexManager.hpp"
#include "attribute_manager/TexCoordManager.hpp"

#include "common/UniqueVec4Provider.hpp"
#include "object/ArrayBufferObject.hpp"
#include "common/UntypedArray.hpp"

#include "pipeline/index_provider/NaturalOrderIndexProvider.hpp"
#include "pipeline/index_provider/ArrayIndexProvider.hpp"

#include "shader/VertexShader.hpp"
#include "shader/NoLightVertexShader.hpp"
#include "shader/SimpleFragmentShader.hpp"
#include "shader/FragmentShader.hpp"
#include "pipeline/PrimitiveIndex.hpp"
#include "pipeline/FrameBuffer.hpp"

#include "pipeline/interpolator/WindowCoordinatesInterpolator.hpp"
#include "pipeline/rasterizer/PointRasterizer.hpp"
#include "pipeline/rasterizer/SimpleLineRasterizer.hpp"
#include "pipeline/rasterizer/TriangleRasterizer.hpp"

#include "pipeline/clipper/PointClipper.hpp"
#include "pipeline/clipper/LineClipper.hpp"
#include "pipeline/clipper/TriangleClipper.hpp"

#include "pipeline/ClippedPrimitiveGroup.hpp"

#include "SDLPixelDrawer.hpp"
namespace my_gl {


     using boost::extents;

     SoftContext::SoftContext(size_t width,size_t height)
     {

	  _height=height;
	  _width=width;

	  //init vec4 manager;
	  _allVec4Manager.replace(int(BindState::NORMAL),new NormalManager());
	  _allVec4Manager.replace(int(BindState::COLOR),new ColorManager());
	  _allVec4Manager.replace(int(BindState::VERTEX),new VertexManager());
	  _allVec4Manager.replace(int(BindState::TEXCOORD),new TexCoordManager());

	  //init active streams
	  //if light is not turned on,texture and normal will not transfered

	  _activeStreams.push_back(BindState::VERTEX);
	  _activeStreams.push_back(BindState::COLOR);

	  _pixelDrawerPtr.reset(new SDLPixelDrawer());
	  _pixelDrawerPtr->onInit(width,height);

	  //init vertex shader
	  //default light is disabled,use NoLightVertexShader

	  //TODO group state related change to one 
	  _vertexShaderPtr.reset(new NoLightVertexShader());
	  _fragmentShaderPtr.reset(new SimpleFragmentShader());
	  

	  //init clippers;

	  _clippers.replace(int(PrimitiveMode::POINTS),
		    new PointClipper());
	  _clippers.replace(int(PrimitiveMode::LINES),
		    new LineClipper());
	  _clippers.replace(int(PrimitiveMode::TRIANGLES),
		    new TriangleClipper());

	  //then rasterizers

	  _fragmentAttributeBufferPtr.reset(new 
		    FragmentAttributeBuffer(width,height,
			 VertexAttributeBuffer::DEFAULT_OUT_SIZE));
	  _frameBufferPtr.reset(new 
		    FrameBuffer(width,height));

	  _interpolatorPtr.reset(new WindowCoordinatesInterpolator());
	  //init rasterizers

	  _rasterizers.replace(int(PrimitiveMode::POINTS),
		    new PointRasterizer(_viewportParameter,
			 *_interpolatorPtr,*_fragmentAttributeBufferPtr));

	  _rasterizers.replace(int(PrimitiveMode::LINES),
		    new SimpleLineRasterizer
		    (_viewportParameter,
			 *_interpolatorPtr,*_fragmentAttributeBufferPtr));

	  Rasterizer *pLineRasterizer=&_rasterizers[1];

	  //what triangle rasterizer do is depends on 
	  //its internal LineRasterizer
	  _rasterizers.replace(int(PrimitiveMode::TRIANGLES),
		    new TriangleRasterizer
		    (_viewportParameter,
			 *_interpolatorPtr,
			 *_fragmentAttributeBufferPtr,
			 static_cast<LineRasterizer*>(pLineRasterizer)));
     }

     SoftContext::~SoftContext(){}

     SoftContext& SoftContext::getInstance()
     {
	  static SoftContext instance;
	  return instance;
     }

     void SoftContext::flush()
     {
	  _pixelDrawerPtr->onFlush();
     }

     void SoftContext::genBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.genBuffers(size,names);
     }

     void SoftContext::deleteBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.deleteBuffers(size,names);
     }

     void SoftContext::clearColor(float r,float g,float b,float a)
     {
	  _frameBufferPtr->clearColor(r,g,b,a);
     }

     void SoftContext::clear(FrameBufferMask frameBufferMask)
     {
	  //currently,only color buffer bit clear is supported

	  if (frameBufferMask|COLOR_BUFFER_BIT)
	  {
	       //may be refactor to use ptr_array 
	       //to store ColorFrameBuffer and 
	       //DepthFrameBuffer
	       _frameBufferPtr->clear();
	  }
     }

     bool SoftContext::isBuffer(Name name) const 
     {
	  return _arrayBufferObjectManager.isBuffer(name);
     }
 	
     void SoftContext::bindBuffer(BufferTarget target,Name name)
     {
	  _arrayBufferObjectManager.bindBuffer(target,name);
     }

     void SoftContext::bufferData(BufferTarget target,size_t size,
		    const void* data, DataUsage usage)
     {
	  _arrayBufferObjectManager.bufferData(target, size, data, usage);
     }

     void SoftContext::bufferSubData(BufferTarget target,ptrdiff_t offset,
		    size_t size,const void* data)
     {
	  _arrayBufferObjectManager.bufferSubData(target,offset,size,data);
     }

     void SoftContext::enableClientState(BindState bindState)
     {
	  assert(bindState!=BindState::ELEMENTS);

	  _allVec4Manager[int(bindState)].enableVertexArray(true);
     }

     void SoftContext::disableClientState(BindState bindState)
     {
	  assert(bindState!=BindState::ELEMENTS);

	  _allVec4Manager[int(bindState)].enableVertexArray(false);
     }


     void SoftContext::normal3f(float nx,float ny,float nz)
     {
	  getVec4Manager<NormalManager>().normal3f(nx,ny,nz);
     }

     void SoftContext::normalPointer(DataType type,size_t stride, const void *pointer)
     {
	  getVec4Manager<NormalManager>().normalPointer(type, stride, pointer);
     }

     void SoftContext::color4f(float red,float green,
		  float blue,float alpha) 
     {
	  getVec4Manager<ColorManager>().
	       color4f(red, green, blue, alpha);;
     }
	void SoftContext::color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) 
	{
	     getVec4Manager<ColorManager>().
		  color4ub(red, green, blue, alpha);
	}

	void SoftContext::colorPointer(int componentSize,
		  DataType type,size_t stride,const void *pointer)
	{
	     getVec4Manager<ColorManager>().
		  colorPointer(componentSize, type, stride, pointer);
	}

	void SoftContext::vertexPointer(int componentSize, 
		  DataType type, size_t stride, const void* pointer)
	{
	     getVec4Manager<VertexManager>().vertexPointer
		  (componentSize, type, stride, pointer);
	}

	void SoftContext::texCoordPointer(int componentSize, 
		  DataType type, size_t stride, const void* pointer)
	{
	     getVec4Manager<TexCoordManager>().texCoordPointer
		  (componentSize, type, stride, pointer);
	}

	void SoftContext::matrixMode(MatrixMode matrixMode) 
	{
	     _matrixMode=matrixMode;
	}

	MatrixStack& SoftContext::currentMatrixStack()
	{return _matrixStacks[int(_matrixMode)];}

	void SoftContext::pushMatrix()
	{
	     currentMatrixStack().push();
	}

	void SoftContext::popMatrix()
	{
	     currentMatrixStack().pop();
	}

	void SoftContext::scalef(float x,float y, float z) 
	{
	     multMatrixf(Matrix::scale(x, y, z));
	}

	void SoftContext::translatef(float x, float y, float z) 
	{
	     multMatrixf(Matrix::translate(x, y, z));
	}

	void SoftContext::rotatef(float angle, float x, float y, float z) 
	{
	     multMatrixf(Matrix::rotate(angle, x, y, z));
	}

	void SoftContext::multMatrixf(const Matrix& matrix)
	{
	     currentMatrixStack().multiTop
		  (matrix);
	}

	void SoftContext::multMatrixf(const float* matrix) 
	{
	     multMatrixf(Matrix(matrix,false));
	}

	void SoftContext::drawArrays(PrimitiveMode primitiveMode, int first, size_t count)
	{
	     //TODO GL spec : if GL_VERTEX_ARRAY is not enabled ,no geom constructed

	     enterPipeline(primitiveMode,count,
		       NaturalOrderIndexProvider(first));

	}

	void SoftContext::drawElements
	     (PrimitiveMode primitiveMode, size_t count, 
		  DataType dataType, const void* indices)
	{
	     //TODO
	     assert(dataType==DataType::UNSIGNED_BYTE || 
		       dataType==DataType::UNSIGNED_SHORT);

	     enterPipeline(primitiveMode,count,
		       _elementIndexManager.elements(
			    primitiveMode,count,dataType,indices));

	}

	void SoftContext::enterPipeline
	     (PrimitiveMode primitiveMode,size_t count,
	      const IndexProvider& indexProvider)
	{

	     prepareGlobalUniform();

	     vertexShaderStage(count,indexProvider);

	     //primitive assemble
	     //use index ref approach
	     PrimitiveIndex primitiveIndex(
		       primitiveMode,count,
		       NaturalOrderIndexProvider());

	     PrimitiveMode catalog=PrimitiveMode::POINTS;

	     switch (primitiveMode)
	     {
		  case PrimitiveMode::LINES:
		  case PrimitiveMode::LINE_LOOP:
		  case PrimitiveMode::LINE_STRIP:
		       {catalog=PrimitiveMode::LINES;
			   break;}
		  case PrimitiveMode::TRIANGLE_FAN:
		  case PrimitiveMode::TRIANGLE_STRIP:
		  case PrimitiveMode::TRIANGLES:
			   {
				catalog=PrimitiveMode::TRIANGLES;
				break;
			   }
			 default:
			   {
				//impossble
				assert(false);
			   }
	     }

	     clipPrimitive(primitiveIndex,catalog);

	     rasterizePrimitive(catalog);

	     fragmentShaderStage();

	     _pixelDrawerPtr->onDraw(*_frameBufferPtr);
	}

	     void SoftContext::fragmentShaderStage()
	     {

		  auto activeFragWinCoords=_fragmentAttributeBufferPtr
		       ->getActiveFragWinCoords();

		  for(auto &winCoord:activeFragWinCoords)
		       {
			    _fragmentShaderPtr->shade(
				      (*_fragmentAttributeBufferPtr)(winCoord),
				      (*_frameBufferPtr)(winCoord));
		       }

	     }

	void SoftContext::rasterizePrimitive(PrimitiveMode catalog)
	{

	     _fragmentAttributeBufferPtr->clear();
	     //choose rasterizer

	     Rasterizer& rasterizer=_rasterizers[int(catalog)];

	     //write FragmentAttributeBuffer 
	     rasterizer.rasterize(*_clippedPrimitiveGroupPtr);

	}

	void SoftContext::clipPrimitive
	     (const PrimitiveIndex& primitiveIndex,PrimitiveMode catalog)
	     {
		  //choose right clipper
		  Clipper& clipper=_clippers[int(catalog)];
		  
		  //reset ClippedPrimitiveGroup

		  _clippedPrimitiveGroupPtr.reset(
			    new ClippedPrimitiveGroup
			    (_vertexAttributeBuffer,
			     primitiveIndex.primitiveMode()));

		  clipper.clip(_vertexAttributeBuffer,
			    primitiveIndex,*_clippedPrimitiveGroupPtr);

	     }


	void SoftContext::vertexShaderStage(size_t vertexNumber,
		  const IndexProvider& indexProvider)
	{

	     _vertexAttributeBuffer.resize(vertexNumber);

	     Vec4 inStream[4];


	     for (size_t vertexCounter=0; vertexCounter<vertexNumber;
		       ++vertexCounter)
	     {
		  int thisVertexIndex=
		       indexProvider.getIndex(vertexCounter);

		  for (auto activeStream:_activeStreams)
		  {
		       //only transfer active streams
		       int streamIdx=int(activeStream);
		       auto& provider=_allVec4Manager[streamIdx];
		       inStream[streamIdx]=
			    provider.getValue(thisVertexIndex);
		  }

		  _vertexShaderPtr->shade(_global,inStream,
			    _vertexAttributeBuffer[vertexCounter]);
	     }
	     
	     //TODO


	}

	void SoftContext::frustumf(float left, float right, 
		  float bottom, float top, 
		  float near, float far)
	{
	     assert(near>0);
	     Matrix matrix;

	     float A=(right+left)/(right-left),
		   B=(top+bottom)/(top-bottom),
		   C=-(far+near)/(far-near),
		   D=-2*(far*near)/(far-near);

	     matrix(3,3)=0;

	     matrix(0,0)=2*near/(right-left);

	     matrix(1,1)=2*near/(top-bottom);

	     matrix(0,2)=A;
	     matrix(1,2)=B;
	     matrix(2,2)=C;
	     matrix(2,3)=D;
	     matrix(3,2)=-1;
	     matrix(3,3)=1;

	     _matrixStacks[int(MatrixMode::PROJECTION)].
		  multiTop(matrix);

	}

	//glOrtho
	void SoftContext::orthof(float left,float right,
		  float bottom,float top,
		  float near,float far)
	{
	     float tx=-(right+left)/(right-left),
	     ty=-(top+bottom)/(top-bottom),
	     tz=-(far+near)/(far-near);


	     Matrix matrix;
	     matrix(0,0)=2/(right-left);
	     matrix(1,1)=2/(top-bottom);
	     matrix(2,2)=-2/(far-near);

	     matrix(0,3)=tx;
	     matrix(1,3)=ty;
	     matrix(2,3)=tz;
	     matrix(3,3)=1;

	     _matrixStacks[int(MatrixMode::PROJECTION)]
		  .multiTop(matrix);
	}

	void SoftContext::prepareGlobalUniform()
	{
	     _global.modelView=_matrixStacks
		  [int(MatrixMode::MODEL_VIEW)].top();
	     _global.modelViewInverse=
		  _global.modelView.inverse();
	     _global.modelViewInverseTranspose=
		  _global.modelViewInverse.transpose();

	     _global.projection=
		  _matrixStacks[int(MatrixMode::PROJECTION)].top();
	     _global.projectionInverse=
		  _global.projection.inverse();
	     _global.projectionInverseTranspose=
		  _global.projectionInverse.transpose();

	     _global.modelViewProjection=
		  _global.projection;
	     _global.modelViewProjection*=_global.modelView;
	     _global.modelViewProjectionInverse=
		  _global.modelViewProjection.inverse();
	     _global.modelViewProjectionInverseTranspose=
		  _global.modelViewProjectionInverse.transpose();

	     _global.texture=_matrixStacks
		  [int(MatrixMode::TEXTURE)].top();
	     _global.textureInverse=
		  _global.texture.inverse();
	     _global.textureInverseTranspose=
		  _global.textureInverse.transpose();

	}

	void SoftContext::viewport(int x,int y,
		  size_t width,size_t height)
	{
	     _viewportParameter=
		  {x,y,width,height};
	}

	void SoftContext::loadIdentity()
	{
	     currentMatrixStack().top()=Matrix::identity();
	}


     template<typename T>
	  T& SoftContext::getVec4Manager()
	  { return static_cast<T&>(_allVec4Manager
		    [int(T::BIND_STATE)]);}

     ObjectNameManager& SoftContext::getObjectNameManager()
     {
	  return _objectNameManager;
     }
	
} /* my_gl */
