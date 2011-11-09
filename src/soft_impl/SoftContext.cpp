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
#include <algorithm>

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
#include "shader/LightVertexShader.hpp"
#include "shader/TextureFragmentShader.hpp"
#include "shader/SimpleFragmentShader.hpp"
#include "shader/TwoSideLightVertexShader.hpp"
#include "shader/FragmentShader.hpp"
#include "pipeline/PrimitiveIndex.hpp"
#include "pipeline/ColorBuffer.hpp"
#include "pipeline/DepthBuffer.hpp"
#include "object/TextureObject.hpp"

#include "pipeline/interpolator/WinCoordInterpolator.hpp"
#include "pipeline/rasterizer/PointRasterizer.hpp"
#include "pipeline/rasterizer/SimpleLineRasterizer.hpp"
#include "pipeline/rasterizer/TriangleRasterizer.hpp"

#include "pipeline/clipper/PointClipper.hpp"
#include "pipeline/clipper/LineClipper.hpp"
#include "pipeline/clipper/TriangleClipper.hpp"

#include "pipeline/ClippedPrimitiveGroup.hpp"

#include "SDLPixelDrawer.hpp"

namespace my_gl {

     using std::remove;

     using boost::extents;

     SoftContext::SoftContext(size_t width,size_t height)
	  :_arrayBufferObjectManager(_objectNameManager),
	  _textureObjectManager(_objectNameManager)
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
	  _lightingEnabled=false;

	  _twoSideLightingEnabled=false;

	  switchShader();
	  

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

	  _allFrameBuffer.replace(ColorBuffer::ORDER_INDEX,
		    new ColorBuffer(width,height));

	  _allFrameBuffer.replace(DepthBuffer::ORDER_INDEX,
		    new DepthBuffer(width,height));

	  _interpolatorPtr.reset(new WinCoordInterpolator());
	  //init rasterizers

	  _rasterizers.replace(int(PrimitiveMode::POINTS),
		    new PointRasterizer(_viewportParameter,
			 *_interpolatorPtr,*_fragmentAttributeBufferPtr,
			 getFrameBuffer<DepthBuffer>(),_depthRange));

	  _rasterizers.replace(int(PrimitiveMode::LINES),
		    new SimpleLineRasterizer
		    (_viewportParameter,
			 *_interpolatorPtr,*_fragmentAttributeBufferPtr,
			 getFrameBuffer<DepthBuffer>(),_depthRange));

	  Rasterizer *pLineRasterizer=&_rasterizers[1];

	  //what triangle rasterizer do is depends on 
	  //its internal LineRasterizer
	  _rasterizers.replace(int(PrimitiveMode::TRIANGLES),
		    new TriangleRasterizer
		    (_viewportParameter,
			 *_interpolatorPtr,
			 *_fragmentAttributeBufferPtr,
			 getFrameBuffer<DepthBuffer>(),
			 _depthRange,
			 static_cast<LineRasterizer*>(pLineRasterizer)));

	  setInstance(this);
     }

     SoftContext::~SoftContext(){}

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
	  getFrameBuffer<ColorBuffer>().clearColor(r,g,b,a);
     }

     void SoftContext::depthRange(float near,float far)
     {
	  _depthRange.near=near;
	  _depthRange.far=far;
     }

     void SoftContext::depthFunc(DepthFunc func)
     {
	  getFrameBuffer<DepthBuffer>().depthFunc(func);
     }

     void SoftContext::clear(FrameBufferMask frameBufferMask)
     {
	  //currently,only color buffer bit clear is supported

	  if (frameBufferMask&COLOR_BUFFER_BIT)
	  {
	       //may be refactor to use ptr_array 
	       //to store ColorColorBuffer and 
	       //DepthColorBuffer
	       getFrameBuffer<ColorBuffer>().clear();
	  }

	  if (frameBufferMask&DEPTH_COLOR_BUFFER_BIT)
	  {
	       getFrameBuffer<DepthBuffer>().clear();
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
	     multMatrixf(scale(x, y, z));
	}

	void SoftContext::translatef(float x, float y, float z) 
	{
	     multMatrixf(translate(x, y, z));
	}

	void SoftContext::rotatef(float angle, float x, float y, float z) 
	{
	     multMatrixf(rotate(angle, x, y, z));
	}
	
	void SoftContext::loadMatrixf(float m[16])
	{
	     currentMatrixStack().top()=Matrix4(m);
	}

	void SoftContext::multiMatrixf(float m[16])
	{
	     multMatrixf(Matrix4(m));
	}


	void SoftContext::multMatrixf(const Matrix4& matrix)
	{
	     currentMatrixStack().multiTop
		  (matrix);
	}

	void SoftContext::multMatrixf(const float* matrix) 
	{
	     multMatrixf(Matrix4(matrix));
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

	     _pixelDrawerPtr->onDraw(getFrameBuffer<ColorBuffer>());
	}

	     void SoftContext::fragmentShaderStage()
	     {

		  auto activeFragWinCoords=_fragmentAttributeBufferPtr
		       ->getActiveFragWinCoords();

		  _fragmentShaderPtr->setTextureObject
		       (_textureObjectManager.getActiveTextureObject());

		  for(auto &winCoord:activeFragWinCoords)
		       {
			    _fragmentShaderPtr->shade(
				      (*_fragmentAttributeBufferPtr)(winCoord),
				      getFrameBuffer<ColorBuffer>()(winCoord));
		       }

	     }

	void SoftContext::rasterizePrimitive(PrimitiveMode catalog)
	{
	     _depthRange.update();

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

		  _vertexShaderPtr->shade(inStream,
			    _vertexAttributeBuffer[vertexCounter]);
	     }
	     
	     //TODO


	}

	void SoftContext::frustumf(float left, float right, 
		  float bottom, float top, 
		  float near, float far)
	{
	     assert(near>0);
	     Matrix4 matrix;

	     float A=(right+left)/(right-left),
		   B=(top+bottom)/(top-bottom),
		   C=-(far+near)/(far-near),
		   D=-2*(far*near)/(far-near);

	     matrix(3,3)=0;

	     matrix(0,0)=2*near/(right-left);

	     matrix(1,1)=2*near/(top-bottom);

	     matrix(2,0)=A;
	     matrix(2,1)=B;
	     matrix(2,2)=C;
	     matrix(3,2)=D;
	     matrix(2,3)=-1;
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


	     Matrix4 matrix;
	     matrix(0,0)=2/(right-left);
	     matrix(1,1)=2/(top-bottom);
	     matrix(2,2)=-2/(far-near);

	     matrix(3,0)=tx;
	     matrix(3,1)=ty;
	     matrix(3,2)=tz;
	     matrix(3,3)=1;

	     _matrixStacks[int(MatrixMode::PROJECTION)]
		  .multiTop(matrix);
	}

	void SoftContext::prepareGlobalUniform()
	{
	     _matrixParam.updateAll
		  (_matrixStacks[int(MatrixMode::MODEL_VIEW)].top(),
		  _matrixStacks[int(MatrixMode::PROJECTION)].top(),
		  _matrixStacks[int(MatrixMode::TEXTURE)].top());
	
	}

	void SoftContext::viewport(int x,int y,
		  size_t width,size_t height)
	{
	     _viewportParameter=
		  {x,y,width,height};
	}

	void SoftContext::loadIdentity()
	{
	     currentMatrixStack().top()=Matrix4::identity();
	}

	void SoftContext::lightf(LightIndex lightIndex,
		  LightParamName paramName,float param)
	{
	     _groupLightingParam.lightf
		  (lightIndex,paramName,param);
	}
	  
	void SoftContext::lightModelf
	       (LightParamName paramName,float param)
	       {
		    assert(paramName==LightParamName::TWO_SIDE);
		    _twoSideLightingEnabled=(param!=0);
	       }

	void SoftContext::lightModelfv
	     (LightParamName paramName,const float* param)
	     {
		  _groupLightingParam.lightModelfv(paramName,param);
	     }

	void SoftContext::lightfv(LightIndex lightIndex,
		  LightParamName paramName,const float* param)
	{
	     _groupLightingParam.lightfv(lightIndex,paramName,param);
	}

	void SoftContext::materialf
	     (Face face,LightParamName paramName,float param)
	     {
		  _groupLightingParam.materialf(face,paramName,param);
	     }

	void SoftContext::materialfv
	     (Face face,LightParamName paramName,const float *param)
	     {
		  _groupLightingParam.materialfv(face,paramName,param);
	     }
	
	void SoftContext::genTextures(size_t n,Name * names)
	{
	     _textureObjectManager.genTextures(n,names);
	}

	void SoftContext::bindTexture
	     (TexTarget target/* ignored*/,Name texture)
	     {
		  _textureObjectManager.bindTexture(target,texture);
	     }

	void SoftContext::deleteTextures(size_t n,Name *names)
	{
	     _textureObjectManager.deleteTextures(n,names);
	}

	void SoftContext::texEnvi(int target/*ignored*/,
		  int pname/* ignored*/,TexEnvMode texEnvMode)
	{
	     _textureFunc=TextureFunc(texEnvMode);
	}

	void SoftContext::texImage2D
	     (TexTarget/*ignored*/target,int level/* ignored*/
		  ,int internalFormat/*ignored*/,size_t width,
		  //OpenGL ES 1.0 border must be 0
		  size_t height,int border/* ignored */,
		  ImageFormat imageFormat,StoreType storeType,
		  const void *texels)
	{
	     _textureObjectManager.texImage2D(target,level,internalFormat,
		       width,height,border,imageFormat,storeType,texels);
	}

	void SoftContext::texSubImage2D(TexTarget/*ignored*/target,
		  int level/* ignored*/,
		  int xoffset,int yoffset,
		  size_t width,size_t height,
		  ImageFormat imageFormat,
		  StoreType storeType,
		  const void *texels)
	{
	     _textureObjectManager.texSubImage2D(target,level,
		       xoffset,yoffset,width,height,imageFormat,
		       storeType,texels);
	}


	void SoftContext::texParameter(TexTarget target/*ignored*/,
		  TexWrapName wrapName,
		  TexWrapMode texWrapMode)
	{
	     _textureObjectManager.
		  texParameter(target,wrapName,texWrapMode);
	}

	void SoftContext::texParameter(TexTarget target/*ignored*/,
		  TexFilterName filterName,
		  TexFilterMode texFilterMode)
	{
	     _textureObjectManager.
		  texParameter(target,filterName,texFilterMode);
	}

	void SoftContext::enableLighting()
	{
	     if (!_lightingEnabled)
	     {
		  _lightingEnabled=true;
		  switchShader();
	     }
	}

	void SoftContext::disableLighting()
	{
	     if (_lightingEnabled)
	     {
		  _lightingEnabled=false;
		  switchShader();
	     }
	}
     
	void SoftContext::enable(LightIndex lightIndex)
	{
	     if (_lightingEnabled)
	     {
		  _groupLightingParam.enable(lightIndex);
	     }
	}

	void SoftContext::disable(LightIndex lightIndex)
	{
	     if (!_lightingEnabled)
	     {
		  return;
	     }

	     _groupLightingParam.disable(lightIndex);
	}

	void SoftContext::switchShader()
	{
	     if (_lightingEnabled){
		  if (_twoSideLightingEnabled){
		       _vertexShaderPtr.reset(
				 new TwoSideLightVertexShader
				 (_matrixParam,_groupLightingParam));
		  }
		  else{
		       _vertexShaderPtr.reset(
				 new LightVertexShader(_matrixParam,
				      _groupLightingParam));
		  }
	     }
	     else{
		  _vertexShaderPtr.reset(new 
			    NoLightVertexShader(_matrixParam,
				 _groupLightingParam));
	
	     }

	     if (_textureEnabled){
		  _fragmentShaderPtr.reset(
			    new TextureFragmentShader
			    (_matrixParam,_textureFunc));
	     }
	     else {
		  _fragmentShaderPtr.reset(new 
			    SimpleFragmentShader(_matrixParam));
	     }

	}

	void SoftContext::copyTexImage2D
	     (TexTarget /*ignored*/,int level/* ignored*/,
	      ImageFormat internalFormat/*ignored*/,
	      int x,int y,size_t width,size_t height,
		  int border/*ignored*/)
	     {
		  auto & textureObject=*_textureObjectManager.
		       getActiveTextureObject();

		  textureObject.directBindImage(width,height,internalFormat);

		  for (int i=0; i<height; ++i)
		  {
		       textureObject.directSubImage
			    (0,i,width,
			     getFrameBuffer<ColorBuffer>()(x,y+i).
			     values());
		  }

	     }
 
	void SoftContext::copyTexSubImage2D(
		  TexTarget /*ignored*/,int level/* ignored*/,
		  int internalFormat/*ignored*/,
		  int xoffset,int yoffset,
		  int x,int y,size_t width,size_t height,
		  int border/* ignored */)
	{
	     auto & textureObject  = *_textureObjectManager.
		  getActiveTextureObject();

	     for (int i=0; i<height; ++i)
	     {
		  textureObject.directSubImage
		       (xoffset,yoffset+i,width,
			getFrameBuffer<ColorBuffer>()(x,y+i)
			.values());
	     }
	}

	//glEnable (texture override)
	void SoftContext::enable(TexTarget texTarget)
	{
	     if (!_textureEnabled)
	     {
		  _textureEnabled=true;
		  switchShader();
	     }
	}

	//glDisable (texture override)
	void SoftContext::disable(TexTarget texTarget)
	{
	     if (_textureEnabled)
	     {
		  _textureEnabled=false;
		  switchShader();
	     }
	}

	//glEnable (cullFace override)
	void SoftContext::enableCullFace()
	{
	     static_cast<TriangleRasterizer&>
		  (_rasterizers[int(PrimitiveMode::TRIANGLES)]).
		  enableCullFace();
	}

	//glDisable (cullFace override)
	void SoftContext::disableCullFace()
	{
	     static_cast<TriangleRasterizer&>
		  (_rasterizers[int(PrimitiveMode::TRIANGLES)]).
		  disableCullFace();

	}

	//glFrontFace
	void SoftContext::frontFace(FaceMode faceMode)
	{
	     static_cast<TriangleRasterizer&>
		  (_rasterizers[int(PrimitiveMode::TRIANGLES)]).
		  frontFace(faceMode);
	}


	//glCullFace
	void SoftContext::cullFace(Face face)
	{
	     static_cast<TriangleRasterizer&>
		  (_rasterizers[int(PrimitiveMode::TRIANGLES)]).
		  cullFace(face);
	}




     template<typename T>
	  T& SoftContext::getVec4Manager()
	  { return static_cast<T&>(_allVec4Manager
		    [int(T::BIND_STATE)]);}

     template<typename T>
	  T& SoftContext::getFrameBuffer()
	  {return static_cast<T&>(_allFrameBuffer[T::ORDER_INDEX]);}



     ObjectNameManager& SoftContext::getObjectNameManager()
     {
	  return _objectNameManager;
     }
	
} /* my_gl */
