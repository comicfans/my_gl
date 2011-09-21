/*
 * =====================================================================================
 *
 *       Filename:  SoftContext.hpp
 *
 *    Description:  C++/thread impl of whole opengl pipeline
 *
 *        Version:  1.0
 *        Created:  2011-9-13 15:26:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SOFT_CONTEXT_HPP

#define SOFT_CONTEXT_HPP

#include <boost/ptr_container/ptr_array.hpp>

#include "common/Context.hpp"
#include "object/ObjectNameManager.hpp"
#include "object/ArrayBufferObjectManager.hpp"


namespace my_gl {

     using boost::ptr_array;

     class BufferObject;
     class VectorManager;


     class SoftContext :public Context{
     public:
     	SoftContext ();

     	virtual ~SoftContext ()noexcept;


	//glGenBuffers
	void genBuffers(size_t size,Name *names);
	//glDeleteBuffers
	void deleteBuffers(size_t size,Name *names);
	//glIsBuffer
	bool isBuffer(Name name) const noexcept;

	void vertexPointer(int componentSize,DataType type, 
		  size_t stride, const void* pointer);

	void normal3f(float nx,float ny,float nz)noexcept;

	void normalPointer(DataType type,
		  size_t stride,const void *pointer);

	void color4f(float red,float green,
		  float blue,float alpha) noexcept;

	void color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) noexcept;

	void colorPointer(int componentSize,DataType type,
		  size_t stride,const void *pointer);

	void texCoordPointer(int componentSize, 
		  DataType type, size_t stride, const void* pointer);

	ObjectNameManager& getObjectNameManager();

	static SoftContext& getInstance();
     
     private:

	ObjectNameManager _objectNameManager;

	ArrayBufferObjectManager _arrayBufferObjectManager;

	ptr_array<VectorManager,4> _allVectorManager;

	template<typename T>
	     T& getVectorManager();

     };
	
} /* my_gl */


#endif /* end of include guard: SOFT_CONTEXT_HPP */
