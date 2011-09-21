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

#include "common/UniqueVectorProvider.hpp"
#include "object/ArrayBufferObject.hpp"
#include "common/UntypedArray.hpp"
namespace my_gl {

     SoftContext::SoftContext()
     {
	  _allVectorManager.replace(int(BindState::NORMAL),new NormalManager());
	  _allVectorManager.replace(int(BindState::COLOR),new ColorManager());
	  _allVectorManager.replace(int(BindState::VERTEX),new VertexManager());
	  _allVectorManager.replace(int(BindState::TEXCOORD),new TexCoordManager());
     }

     void SoftContext::genBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.genBuffers(size,names);
     }

     void SoftContext::deleteBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.deleteBuffers(size,names);
     }

     bool SoftContext::isBuffer(Name name) const noexcept
     {
	  return _arrayBufferObjectManager.isBuffer(name);
     }

     void SoftContext::normal3f(float nx,float ny,float nz)noexcept
     {
	  getVectorManager<NormalManager>().normal3f(nx,ny,nz);
     }

     void SoftContext::normalPointer(DataType type,size_t stride, const void *pointer)
     {
	  getVectorManager<NormalManager>().normalPointer(type, stride, pointer);
     }

     void SoftContext::color4f(float red,float green,
		  float blue,float alpha) noexcept
     {
	  getVectorManager<ColorManager>().
	       color4f(red, green, blue, alpha);;
     }
	void SoftContext::color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) noexcept
	{
	     getVectorManager<ColorManager>().
		  color4ub(red, green, blue, alpha);
	}

	void SoftContext::colorPointer(int componentSize,
		  DataType type,size_t stride,const void *pointer)
	{
	     getVectorManager<ColorManager>().
		  colorPointer(componentSize, type, stride, pointer);
	}

	void SoftContext::vertexPointer(int componentSize, 
		  DataType type, size_t stride, const void* pointer)
	{
	     getVectorManager<VertexManager>().vertexPointer
		  (componentSize, type, stride, pointer);
	}

	void SoftContext::texCoordPointer(int componentSize, 
		  DataType type, size_t stride, const void* pointer)
	{
	     getVectorManager<TexCoordManager>().texCoordPointer
		  (componentSize, type, stride, pointer);
	}


     template<typename T>
	  T& SoftContext::getVectorManager()
	  { return static_cast<T&>(_allVectorManager[int(T::BIND_STATE)]);}
	
} /* my_gl */
