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
#include <functional>

// we neeed construct ptr_map mapped_value with many param
#define BOOST_ASSIGN_MAX_PARAMS 7
#include <boost/assign/ptr_map_inserter.hpp>

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
#include "shader/WrapTextureVertexShader.hpp"
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
#include "common/CheckEnum.hpp"

namespace my_gl {

	

     const SoftContext::BindStateAndIndex VERTEX(GL_VERTEX_ARRAY,0);
     const SoftContext::BindStateAndIndex COLOR(GL_COLOR_ARRAY,0);
     const SoftContext::BindStateAndIndex NORMAL(GL_NORMAL_ARRAY,0);
     const SoftContext::BindStateAndIndex TEXCOORD(GL_TEXTURE_COORD_ARRAY,0);

     using std::remove;

     using boost::extents;

     SoftContext::SoftContext(size_t width,size_t height)
	  :_arrayBufferObjectManager(_objectNameManager),
	  _textureObjectManager(_objectNameManager)
     {

	  _height=height;
	  _width=width;

	  //init vec4 manager;
	  boost::assign::ptr_map_insert<VertexManager>
	       (_allVec4Manager)(GL_VERTEX_ARRAY);
	  boost::assign::ptr_map_insert<NormalManager>
	       (_allVec4Manager)(GL_NORMAL_ARRAY);
	  boost::assign::ptr_map_insert<ColorManager>
	       (_allVec4Manager)(GL_COLOR_ARRAY);
	  boost::assign::ptr_map_insert<TexCoordManager>
	       (_allVec4Manager)(GL_TEXTURE_COORD_ARRAY);


	  //init active streams
	  //if light is not turned on,texture and normal will not transfered

	  _activeStreams.push_back(VERTEX);
	  _activeStreams.push_back(COLOR);

	  _pixelDrawerPtr.reset(new SDLPixelDrawer());
	  _pixelDrawerPtr->onInit(width,height);

	  //init vertex shader
	  //default light is disabled,use NoLightVertexShader

	  //TODO group state related change to one 
	  _lightingEnabled=false;
	  _textureEnabled=false;

	  _twoSideLightingEnabled=false;

	  _vertexShaderPtr.reset(new NoLightVertexShader
		    (_matrixParam,_groupLightingParam));
	  _fragmentShaderPtr.reset(new SimpleFragmentShader
		    (_matrixParam));
	  

	  //init clippers;

	  boost::assign::ptr_map_insert<PointClipper>
	       (_clippers)(GL_POINTS);
	  boost::assign::ptr_map_insert<LineClipper>
	       (_clippers)(GL_LINES);
	  boost::assign::ptr_map_insert<TriangleClipper>
	       (_clippers)(GL_TRIANGLES);


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


	  boost::assign::ptr_map_insert<PointRasterizer>(_rasterizers)
	       (GL_POINTS,
		std::ref(_viewportParameter),std::ref(*_interpolatorPtr),
		std::ref(*_fragmentAttributeBufferPtr),
		std::ref(getFrameBuffer<DepthBuffer>()),std::ref(_depthRange));

	  boost::assign::ptr_map_insert<SimpleLineRasterizer>(_rasterizers)
	       (GL_LINES,
		std::ref(_viewportParameter),std::ref(*_interpolatorPtr),
		std::ref(*_fragmentAttributeBufferPtr),
		std::ref(getFrameBuffer<DepthBuffer>()),std::ref(_depthRange));

	  Rasterizer *pLineRasterizer=_rasterizers.find(GL_LINES)->second;

	  //what triangle rasterizer do is depends on 
	  //its internal LineRasterizer
	  boost::assign::ptr_map_insert<TriangleRasterizer>(_rasterizers)
	       (GL_TRIANGLES,
		std::ref(_viewportParameter),std::ref(*_interpolatorPtr),
		std::ref(*_fragmentAttributeBufferPtr),
		std::ref(getFrameBuffer<DepthBuffer>()),std::ref(_depthRange),
		static_cast<LineRasterizer*>(pLineRasterizer));


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

     void SoftContext::deleteBuffers(size_t size,const  Name *names)
     {
	  _arrayBufferObjectManager.deleteBuffers(size,names);
     }

     void SoftContext::clearColor(float r,float g,float b,float a)
     {
	  getFrameBuffer<ColorBuffer>().clearColor(r,g,b,a);
     }

	
     void SoftContext::clearDepth(double depth)
     {
	  getFrameBuffer<DepthBuffer>().clearDepth(depth);
     }
     void SoftContext::depthRange(double nearValue,double farValue)
     {
	  _depthRange.nearValue=nearValue;
	  _depthRange.farValue=farValue;
     }

     void SoftContext::depthFunc(GLenum func)
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

	  if (frameBufferMask&DEPTH_BUFFER_BIT)
	  {
	       getFrameBuffer<DepthBuffer>().clear();
	  }
	  
     }

     bool SoftContext::isBuffer(Name name) const 
     {
	  return _arrayBufferObjectManager.isBuffer(name);
     }
 	
     void SoftContext::bindBuffer(GLenum target,Name name)
     {
	  _arrayBufferObjectManager.bindBuffer(target,name);
     }

     void SoftContext::bufferData(GLenum target,size_t size,
		    const void* data, GLenum usage)
     {
	  _arrayBufferObjectManager.bufferData(target, size, data, usage);
     }

     void SoftContext::bufferSubData(GLenum target,ptrdiff_t offset,
		    size_t size,const void* data)
     {
	  _arrayBufferObjectManager.bufferSubData(target,offset,size,data);
     }

     void SoftContext::enableClientState(GLenum bindState)
     {
	  checkBindState(bindState);

	  assert(bindState!=GL_ELEMENT_ARRAY_BUFFER);

	  auto it=_allVec4Manager.find(bindState);

	  assert(it!=_allVec4Manager.end());

	  it->second->enableVertexArray(true);

     }

     void SoftContext::disableClientState(GLenum bindState)
     {
	  
	  checkBindState(bindState);

	  auto it=_allVec4Manager.find(bindState);

	  assert(it!=_allVec4Manager.end());

	  it->second->enableVertexArray(false);
     }

	
     void SoftContext::copyArrayBufferBind(GLenum bindState)
     {
	  checkBindState(bindState);

	  auto it=_allVec4Manager.find(bindState);

	  assert(it!=_allVec4Manager.end());

	  it->second->bindArrayBufferObject
			 (_arrayBufferObjectManager.getArrayBuffer());
     }

     void SoftContext::normal3f(float nx,float ny,float nz)
     {
	  getVec4Manager<NormalManager>().normal3f(nx,ny,nz);
     }

     void SoftContext::normalPointer
	  (GLenum type,size_t stride, const void *pointer)
     {
	  copyArrayBufferBind(GL_NORMAL_ARRAY);

	  getVec4Manager<NormalManager>().
	       normalPointer(type, stride, pointer);
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
		  GLenum type,size_t stride,const void *pointer)
	{
	     copyArrayBufferBind(GL_COLOR_ARRAY);

	     getVec4Manager<ColorManager>().
		  colorPointer(componentSize, type, stride, pointer);
	}

	void SoftContext::vertexPointer(int componentSize, 
		  GLenum type, size_t stride, const void* pointer)
	{
	  
	     copyArrayBufferBind(GL_VERTEX_ARRAY);

	     getVec4Manager<VertexManager>().vertexPointer
		  (componentSize, type, stride, pointer);
	}

	void SoftContext::texCoordPointer(int componentSize, 
		  GLenum type, size_t stride, const void* pointer)
	{

	     copyArrayBufferBind(GL_TEXTURE_COORD_ARRAY);

	     getVec4Manager<TexCoordManager>().texCoordPointer
		  (componentSize, type, stride, pointer);
	}

	void SoftContext::matrixMode(GLenum matrixMode) 
	{
	     _matrixMode=matrixMode;
	}

	MatrixStack& SoftContext::currentMatrixStack()
	{return _matrixStacks[_matrixMode];}

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
	
	void SoftContext::loadMatrixf(const float m[16])
	{
	     currentMatrixStack().top()=Matrix4(m);
	}

	void SoftContext::multiMatrixf(const float m[16])
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

	void SoftContext::drawArrays(GLenum primitiveMode, int first, size_t count)
	{
	     //TODO GL spec : if GL_VERTEX_ARRAY is not enabled ,no geom constructed

	     enterPipeline(primitiveMode,count,
		       NaturalOrderIndexProvider(first));

	}

	void SoftContext::drawElements
	     (GLenum primitiveMode, size_t count, 
		  GLenum dataType, const void* indices)
	{
	     assert(dataType==GL_UNSIGNED_BYTE || 
		       dataType==GL_UNSIGNED_SHORT);

	     _elementIndexManager.bindArrayBufferObject
		  (_arrayBufferObjectManager.getElementsBuffer());


	     enterPipeline(primitiveMode,count,
		       _elementIndexManager.elements(
			    primitiveMode,count,dataType,indices));

	}

	void SoftContext::enterPipeline
	     (GLenum primitiveMode,size_t count,
	      const IndexProvider& indexProvider)
	{

	     //TODO make param interface updatable
	     //and flush all need param
	     prepareGlobalUniform();
	     _groupLightingParam.updateAll();

	     vertexShaderStage(count,indexProvider);

	     //primitive assemble
	     //use index ref approach
	     PrimitiveIndex primitiveIndex(
		       primitiveMode,count,
		       NaturalOrderIndexProvider());

	     GLenum catalog=GL_POINTS;

	     switch (primitiveMode)
	     {
		  case GL_LINES:
		  case GL_LINE_LOOP:
		  case GL_LINE_STRIP:
		       {catalog=GL_LINES;
			   break;}
		  case GL_TRIANGLE_FAN:
		  case GL_TRIANGLE_STRIP:
		  case GL_TRIANGLES:
			   {
				catalog=GL_TRIANGLES;
				break;
			   }
		  case GL_POINTS:
			   {
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

	void SoftContext::rasterizePrimitive(GLenum catalog)
	{
	     _depthRange.update();

	     _fragmentAttributeBufferPtr->clear();
	     //choose rasterizer

	     Rasterizer& rasterizer=*(_rasterizers.find(catalog)->second);

	     //write FragmentAttributeBuffer 
	     rasterizer.rasterize(*_clippedPrimitiveGroupPtr);

	}

	void SoftContext::clipPrimitive
	     (const PrimitiveIndex& primitiveIndex,GLenum catalog)
	     {
		  //choose right clipper
		  auto it=_clippers.find(catalog);

		  assert(it!=_clippers.end());

		  Clipper& clipper=*(it->second);
		  
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
		       auto it = _allVec4Manager.find(activeStream.first);

		       assert(it!=_allVec4Manager.end());

		       auto& provider=*(it->second);
			    
		       inStream[activeStream.second]=
			    provider.getValue(thisVertexIndex);
		  }

		  _vertexShaderPtr->shade(inStream,
			    _vertexAttributeBuffer[vertexCounter]);
	     }
	     
	}

	void SoftContext::frustum(double left, double right, 
		  double bottom, double top, 
		  double near, double far)
	{
	     assert(near>0);
	     Matrix4 matrix;

	     double A=(right+left)/(right-left),
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

	     _matrixStacks[GL_PROJECTION].
		  multiTop(matrix);

	}

	//glOrthof
	void SoftContext::ortho(double left,double right,
		  double bottom,double top,
		  double near,double far)
	{
	     double tx=-(right+left)/(right-left),
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

	     _matrixStacks[GL_PROJECTION]
		  .multiTop(matrix);
	}

	void SoftContext::prepareGlobalUniform()
	{
	     _matrixParam.updateAll
		  (_matrixStacks[GL_MODELVIEW].top(),
		  _matrixStacks[GL_PROJECTION].top(),
		  _matrixStacks[GL_TEXTURE].top());
	
	}

	void SoftContext::viewport(int x,int y,
		  size_t width,size_t height)
	{
	     _viewportParameter=
		  {x,y,uint32_t(width),uint32_t(height)};
	}

	void SoftContext::loadIdentity()
	{
	     currentMatrixStack().top()=Matrix4::identity();
	}

	void SoftContext::lightf(GLenum lightIndex,
		  GLenum paramName,float param)
	{
	     _groupLightingParam.lightf
		  (lightIndex,paramName,param);
	}
	  
	void SoftContext::lightModelf
	       (GLenum paramName,float param)
	       {
		    assert(paramName==GL_LIGHT_MODEL_TWO_SIDE);
		    _twoSideLightingEnabled=(param!=0);
	       }

	void SoftContext::lightModelfv
	     (GLenum paramName,const float* param)
	     {
		  _groupLightingParam.lightModelfv(paramName,param);
	     }

	void SoftContext::lightfv(GLenum lightIndex,
		  GLenum paramName,const float* param)
	{
	     _groupLightingParam.lightfv(lightIndex,paramName,param,
		       _matrixStacks[GL_MODELVIEW].
		       top());
	}

	void SoftContext::materialf
	     (GLenum face,GLenum paramName,float param)
	     {
		  _groupLightingParam.materialf(face,paramName,param);
	     }

	void SoftContext::materialfv
	     (GLenum face,GLenum paramName,const float *param)
	     {
		  _groupLightingParam.materialfv(face,paramName,param);
	     }
	
	void SoftContext::genTextures(size_t n,Name * names)
	{
	     _textureObjectManager.genTextures(n,names);
	}

	void SoftContext::bindTexture
	     (GLenum target/* ignored*/,Name texture)
	     {
		  _textureObjectManager.bindTexture(target,texture);
	     }

	void SoftContext::deleteTextures(size_t n,const Name *names)
	{
	     _textureObjectManager.deleteTextures(n,names);
	}

	bool SoftContext::isTexture(Name name)
	{
	     return _textureObjectManager.isTexture(name);
	}

	void SoftContext::texEnvf(int target/*ignored*/,
		  int pname/* ignored*/,TexEnvMode texEnvMode)
	{
	     _textureFunc=TextureFunc(texEnvMode);
	}

	void SoftContext::texImage2D
	     (GLenum/*ignored*/target,int level/* ignored*/
		  ,int internalFormat/*ignored*/,size_t width,
		  //OpenGL ES 1.0 border must be 0
		  size_t height,int border/* ignored */,
		  GLenum imageFormat,GLenum storeType,
		  const void *texels)
	{
	     _textureObjectManager.texImage2D(target,level,internalFormat,
		       width,height,border,imageFormat,storeType,texels);
	}

	void SoftContext::texSubImage2D(GLenum/*ignored*/target,
		  int level/* ignored*/,
		  int xoffset,int yoffset,
		  size_t width,size_t height,
		  GLenum imageFormat,
		  GLenum storeType,
		  const void *texels)
	{
	     _textureObjectManager.texSubImage2D(target,level,
		       xoffset,yoffset,width,height,imageFormat,
		       storeType,texels);
	}



	void SoftContext::texParameteri(GLenum target/*ignored*/,
		  TexWrapName wrapName,
		  TexWrapMode texWrapMode)
	{
	     _textureObjectManager.
		  texParameter(target,wrapName,texWrapMode);
	}

	void SoftContext::texParameteri(GLenum target/*ignored*/,
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
		  lightingStateChange();
	     }
	}

	void SoftContext::disableLighting()
	{
	     if (_lightingEnabled)
	     {
		  _lightingEnabled=false;
		  lightingStateChange();
	     }
	}
	       
	void SoftContext::enableNormal(GLenum normalizeNormal)
	{
	     _vertexShaderPtr->enable(normalizeNormal);
	}

	       
	void SoftContext::disableNormal(GLenum normalizeNormal)
	{
	     _vertexShaderPtr->disable(normalizeNormal);
	}


	void SoftContext::enableLightN(GLenum lightIndex)
	{
	     if (_lightingEnabled)
	     {
		  _groupLightingParam.enable(lightIndex);
	     }
	}

	void SoftContext::disableLightN(GLenum lightIndex)
	{
	     if (!_lightingEnabled)
	     {
		  return;
	     }

	     _groupLightingParam.disable(lightIndex);
	}

	static void uniqueProcess(vector<pair<GLenum,int>>& all,SoftContext::BindStateAndIndex toProcess,bool add)
	{
		  auto pos=find(all.begin(),all.end(),toProcess);

		  bool has=(pos!=all.end());
		  if (add)
		  {
		       if (!has)
		       {
		       all.push_back(toProcess);
		       }
		       return;
		  }
		  else
		  {
		       if (has)
		       {
			    all.erase(pos);
		       }
		       return;
		  }
	}




	void SoftContext::lightingStateChange()
	{

	     //enable NORMAL if lighting is enabled
	     //remove if disabled
	     uniqueProcess(_activeStreams,NORMAL,_lightingEnabled);
	     //when lighting is enabled, color is decided by lighting param
	     uniqueProcess(_activeStreams,COLOR,!_lightingEnabled);


	     unique_ptr<VertexShader> finalPtr;
	     
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

	     if (_textureEnabled)
	     {
		  _vertexShaderPtr.reset(
			    new WrapTextureVertexShader
			    (_matrixParam,_groupLightingParam,
			     _vertexShaderPtr.release()));
	
	     }
	     
	}

	void SoftContext::textureStateChange()
	{

	     //enable TEXCOORD if texture is enabled
	     //remove if disable
	     uniqueProcess(_activeStreams,TEXCOORD,_textureEnabled);

	     if (_textureEnabled){

		  _vertexShaderPtr.reset(
			    new WrapTextureVertexShader
			    (_matrixParam,_groupLightingParam,
			     _vertexShaderPtr.release()));
	
		  _fragmentShaderPtr.reset(
			    new TextureFragmentShader
			    (_matrixParam,_textureFunc));
	     }
	     else {
		  _fragmentShaderPtr.reset(new 
			    SimpleFragmentShader(_matrixParam));

		  WrapTextureVertexShader *box=static_cast
		       <WrapTextureVertexShader*>(_vertexShaderPtr.release());

		  _vertexShaderPtr.reset(box->releaseWrapped());
	     }

	}

	void SoftContext::copyTexImage2D
	     (GLenum /*ignored*/,int level/* ignored*/,
	      GLenum internalFormat/*ignored*/,
	      int x,int y,size_t width,size_t height,
		  int border/*ignored*/)
	     {
		  auto & textureObject=*_textureObjectManager.
		       getActiveTextureObject();

		  textureObject.directBindImage(width,height,internalFormat);

		  for (size_t i=0; i<height; ++i)
		  {
		       textureObject.directSubImage
			    (0,i,width,
			     getFrameBuffer<ColorBuffer>()(x,y+i).
			     values());
		  }

	     }
 
	void SoftContext::copyTexSubImage2D(
		  GLenum /*ignored*/,int level/* ignored*/,
		  int xoffset,int yoffset,
		  int x,int y,size_t width,size_t height)
	{
	     auto & textureObject  = *_textureObjectManager.
		  getActiveTextureObject();

	     for (size_t i=0; i<height; ++i)
	     {
		  textureObject.directSubImage
		       (xoffset,yoffset+i,width,
			getFrameBuffer<ColorBuffer>()(x,y+i)
			.values());
	     }
	}

	//glEnable (texture override)
	void SoftContext::enableTexTarget(GLenum texTarget)
	{
	     if (!_textureEnabled)
	     {
		  _textureEnabled=true;
		  textureStateChange();
	     }
	}

	//glDisable (texture override)
	void SoftContext::disableTexTarget(GLenum texTarget)
	{
	     if (_textureEnabled)
	     {
		  _textureEnabled=false;
		  textureStateChange();
	     }
	}

	//glEnable (cullFace override)
	void SoftContext::enableCullFace()
	{
	     auto it = _rasterizers.find(GL_TRIANGLES);

	     assert(it!=_rasterizers.end());

	     static_cast<TriangleRasterizer*>(it->second)->enableCullFace();
	}

	//glDisable (cullFace override)
	void SoftContext::disableCullFace()
	{
	     auto it = _rasterizers.find(GL_TRIANGLES);

	     assert(it!=_rasterizers.end());

	     static_cast<TriangleRasterizer*>(it->second)->disableCullFace();
	
	}

	//glFrontFace
	void SoftContext::frontFace(GLenum faceMode)
	{
	     auto it = _rasterizers.find(GL_TRIANGLES);

	     assert(it!=_rasterizers.end());

	     static_cast<TriangleRasterizer*>(it->second)->frontFace(faceMode);
	}


	//glCullFace
	void SoftContext::cullFace(GLenum face)
	{
	     auto it = _rasterizers.find(GL_TRIANGLES);

	     assert(it!=_rasterizers.end());

	     static_cast<TriangleRasterizer*>(it->second)->cullFace(face);
	}




     template<typename T>
	  T& SoftContext::getVec4Manager()
	  { 
	       auto it = _allVec4Manager.find(T::BIND_STATE);
	       assert(it!=_allVec4Manager.end());
	       return static_cast<T&>(*(it->second));}

     template<typename T>
	  T& SoftContext::getFrameBuffer()
	  {return static_cast<T&>(_allFrameBuffer[T::ORDER_INDEX]);}

	
} /* my_gl */


