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

#include "attribute_manager/NormalManager.hpp"
#include "attribute_manager/ColorManager.hpp"
#include "attribute_manager/VertexManager.hpp"
#include "attribute_manager/TexCoordManager.hpp"

#include "common/UniqueVec4Provider.hpp"
#include "object/ArrayBufferObject.hpp"
#include "common/UntypedArray.hpp"

#include "shader/VertexShader.hpp"
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

	}

	void SoftContext::drawElements(PrimitiveMode primitiveMode, size_t count, 
		  DataType dataType, const void* indices)
	{
	     //TODO
	     assert(dataType==DataType::UNSIGNED_BYTE || 
		       dataType==DataType::UNSIGNED_SHORT);
	     {

	     }
	}

	SoftContext::Vec4ProviderArray 
	     SoftContext::getVec4Provider()
	{
	     Vec4ProviderArray result;

	     for (int i=0; i< 4; ++i)
	     {
		  result[i]=& _allVec4Manager[i].getProvider();
	     }
	     return result;
	}

	void SoftContext::transformVertex(const int vertexNumber)
	{
	     _vertexAttributeBuffer.resize(vertexNumber);

     

	     for (int i=0; i<vertexNumber;++i)
	     {
		  //TODO _vertexShader.shade();
	     }
	     
	     //TODO


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
