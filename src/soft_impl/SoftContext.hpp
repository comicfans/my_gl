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
#include "common/MatrixStack.hpp"
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
	virtual void genBuffers(size_t size,Name *names);
	//glDeleteBuffers
	virtual void deleteBuffers(size_t size,Name *names);
	//glIsBuffer
	virtual bool isBuffer(Name name) const noexcept;

	//glVertexPointer
	virtual void vertexPointer(int componentSize,DataType type, 
		  size_t stride, const void* pointer);

	//glNormal3f
	virtual void normal3f(float nx,float ny,float nz)noexcept;

	//glNormalPointer
	virtual void normalPointer(DataType type,
		  size_t stride,const void *pointer);
	//glColor4f
	virtual void color4f(float red,float green,
		  float blue,float alpha) noexcept;

	//glColor4ub
	virtual void color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) noexcept;

	//glColorPointer
	virtual void colorPointer(int componentSize,DataType type,
		  size_t stride,const void *pointer);

	//glTexCoordPointer
	virtual void texCoordPointer(int componentSize, 
		  DataType type, size_t stride, const void* pointer);

	//glMatrixMode
	virtual void matrixMode(MatrixMode matrixMode)noexcept;

	//glPushMatrix
	virtual void pushMatrix()noexcept;

	//glPopMatrix
	virtual void popMatrix()noexcept;

	//glTranlatef
	virtual void translatef(float x,float y,float z)noexcept;

	//glScalef
	virtual void scalef(float x,float y,float z)noexcept;

	//glRotatef
	virtual void rotatef(float angle,float x,float y,float z)noexcept;

	//glMultMatrixf
	virtual void multMatrixf(const float* matrix)noexcept;

	ObjectNameManager& getObjectNameManager();

	static SoftContext& getInstance();
     
     private:

	ObjectNameManager _objectNameManager;

	ArrayBufferObjectManager _arrayBufferObjectManager;

	ptr_array<VectorManager,4> _allVectorManager;

	template<typename T>
	     T& getVectorManager();

	MatrixMode _matrixMode;

	MatrixStack _matrixStacks[3];

	void multMatrixf(const Matrix& matrix)noexcept;

	MatrixStack& currentMatrixStack() noexcept;

     };
	
} /* my_gl */


#endif /* end of include guard: SOFT_CONTEXT_HPP */
