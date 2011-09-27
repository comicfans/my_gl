/*
 * =====================================================================================
 *
 *       Filename:  Context.hpp
 *
 *    Description:  whole state of a draw context
 *
 *        Version:  1.0
 *        Created:  2011-9-13 15:16:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CONTEXT_HPP

#define CONTEXT_HPP

#include <cstddef>
#include <cstdint>

#include "Typedef.hpp"
#include "Enum.hpp"

namespace my_gl {

     class Context {
     public:

	  //glGenBuffers
	virtual void  genBuffers(size_t size,Name *names)=0;
	//glDeleteBuffers
	virtual void  deleteBuffers(size_t size,Name *names)=0;
	//glIsBuffer
	virtual bool isBuffer(Name name) const noexcept=0;

	//glVertexPointer
	virtual void  vertexPointer(int componentSize,DataType type, 
		  size_t stride, const void * pointer)=0;

	//glNormal3f
	virtual void  normal3f(float nx,float ny,float nz)noexcept=0;

	//glNormalPointer
	virtual void  normalPointer(DataType type,
		  size_t stride,const void  *pointer)=0;
	//glColor4f
	virtual void  color4f(float red,float green,
		  float blue,float alpha) noexcept=0;

	//glColor4ub
	virtual void  color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) noexcept=0;

	//glColorPointer
	virtual void  colorPointer(int componentSize,DataType type,
		  size_t stride,const void  *pointer)=0;

	//glTexCoordPointer
	virtual void  texCoordPointer(int componentSize, 
		  DataType type, size_t stride, const void * pointer)=0;

	//glMatrixMode
	virtual void matrixMode(MatrixMode matrixMode)noexcept=0;

	//glPushMatrix
	virtual void pushMatrix()noexcept=0;

	//glPopMatrix
	virtual void popMatrix()noexcept=0;


	//glTranlatef
	virtual void translatef(float x,float y,float z)noexcept=0;

	//glScalef
	virtual void scalef(float x,float y,float z)noexcept=0;

	//glRotatef
	virtual void rotatef(float angle,float x,float y,float z)noexcept=0;

	//glMultMatrixf
	virtual void multMatrixf(const float* matrix)noexcept=0;


	virtual ~Context()noexcept;
     };
	
} /* my_gl */



#endif /* end of include guard: CONTEXT_HPP */
