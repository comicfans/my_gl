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

#include "shader/VertexShader.hpp"
#include "shader/FragmentShader.hpp"
#include "pipeline/PrimitiveIndex.hpp"
namespace my_gl {


     using boost::extents;

     SoftContext::SoftContext()
     {
	  _allVec4Manager.replace(int(BindState::NORMAL),new NormalManager());
	  _allVec4Manager.replace(int(BindState::COLOR),new ColorManager());
	  _allVec4Manager.replace(int(BindState::VERTEX),new VertexManager());
	  _allVec4Manager.replace(int(BindState::TEXCOORD),new TexCoordManager());
     }

     SoftContext::~SoftContext(){}

     SoftContext& SoftContext::getInstance()
     {
	  static SoftContext instance;
	  return instance;
     }

     void SoftContext::genBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.genBuffers(size,names);
     }

     void SoftContext::deleteBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.deleteBuffers(size,names);
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
	     //use natual array index provider
	     _primitiveIndexPtr.reset(
		       new PrimitiveIndex
		       (primitiveMode, count, 
			/* currently not check array number
			 * (depends on data type,component size,
			 * which is not directly to decide) 
			 * */
			INT_MAX, 
			//drawArrays use NaturalOrderIndexProvider
			NaturalOrderIndexProvider()));

	     transformVertex(count,first);

	     postVertexShaderProcess();

	}

	void SoftContext::drawElements(PrimitiveMode primitiveMode, size_t count, 
		  DataType dataType, const void* indices)
	{
	     //TODO
	     assert(dataType==DataType::UNSIGNED_BYTE || 
		       dataType==DataType::UNSIGNED_SHORT);


	}

	void SoftContext::postVertexShaderProcess()
	{

	}


	void SoftContext::transformVertex(size_t vertexNumber,int offset)
	{
	     _vertexAttributeBuffer.resize(vertexNumber);

		  
	     Vec4 inStream[4];
	     //construct input attribute
		  for (int j=0; j<4; ++j)
		  {
		       auto& provider=_allVec4Manager[j];
		       inStream[j]=provider.value();
		       provider.next(offset);
		  }


	     for (int vertexCounter=0; vertexCounter<vertexNumber;
		       ++vertexCounter)
	     {
		  for (int j=0; j<4; ++j)
		  {
		       auto& provider=_allVec4Manager[j];
		       inStream[j]=provider.value();
		       provider.next();
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



     template<typename T>
	  T& SoftContext::getVec4Manager()
	  { return static_cast<T&>(_allVec4Manager
		    [int(T::BIND_STATE)]);}

     ObjectNameManager& SoftContext::getObjectNameManager()
     {
	  return _objectNameManager;
     }
	
} /* my_gl */
