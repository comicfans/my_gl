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
	virtual bool isBuffer(Name name) const =0;

	//glVertexPointer
	virtual void  vertexPointer(int componentSize,DataType type, 
		  size_t stride, const void * pointer)=0;

	//glNormal3f
	virtual void  normal3f(float nx,float ny,float nz)=0;

	//glNormalPointer
	virtual void  normalPointer(DataType type,
		  size_t stride,const void  *pointer)=0;
	//glColor4f
	virtual void  color4f(float red,float green,
		  float blue,float alpha) =0;

	//glColor4ub
	virtual void  color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) =0;

	//glColorPointer
	virtual void  colorPointer(int componentSize,DataType type,
		  size_t stride,const void  *pointer)=0;

	//glTexCoordPointer
	virtual void  texCoordPointer(int componentSize, 
		  DataType type, size_t stride, const void * pointer)=0;

	//glMatrixMode
	virtual void matrixMode(MatrixMode matrixMode)=0;

	//glPushMatrix
	virtual void pushMatrix()=0;

	//glPopMatrix
	virtual void popMatrix()=0;

	//glLoadMatrix
	virtual void loadMatrixf(const float m[16])=0;

	//gllMultiMatrix
	virtual void multiMatrixf(const float m[16])=0;



	//glTranlatef
	virtual void translatef(float x,float y,float z)=0;

	//glScalef
	virtual void scalef(float x,float y,float z)=0;

	//glRotatef
	virtual void rotatef(float angle,float x,float y,float z)=0;

	//glMultMatrixf
	virtual void multMatrixf(const float* matrix)=0;

	//glFrustumf
	virtual void frustum(double left, double right, 
		  double bottom, double top, 
		  double near, double far)=0;

	//glOrtho
	virtual void ortho(double left,double right,
		  double bottom,double top,
		  double near,double far)=0;

	//glViewport
	virtual void viewport(int x,int y,
		  size_t width,size_t height)=0;

	//glEnableClient
	virtual void enableClientState(BindState bindState)=0;

	//glDisableClient
	virtual void disableClientState(BindState bindState)=0;

	//glDrawArrays 
	virtual void drawArrays(PrimitiveMode primitiveMode,
		  int first,size_t count)=0;

	//glDrawElements 
	virtual void drawElements(PrimitiveMode primitiveMode,
		  size_t count,DataType dataType,const void* indices)=0;

	//glFlush
	virtual void flush()=0;

	//glLoadIdentity
	virtual void loadIdentity()=0;

	//glClear
	virtual void clear(FrameBufferMask frameBufferMask)=0;

	//glClearDepth
	virtual void clearDepth(double depth)=0;

	//glClearColor
	virtual void clearColor(float r,float g,float b,float a)=0;

	//glDepthRange
	virtual void depthRange(double near,double far)=0;

	//glDepthFunc
	virtual void depthFunc(DepthFunc func)=0;


	//glEnable (cullFace override)
	virtual void enableCullFace()=0;

	//glDisable (cullFace override)
	virtual void disableCullFace()=0;

	//glFrontFace
	virtual void frontFace(FaceMode faceMode)=0;

	//glCullFace
	virtual void cullFace(Face face)=0;

	//glEnable lighting
	virtual void enableLighting()=0;

	//glDisable lighting
	virtual void disableLighting()=0;

	//glEnable  (LIGHTn override)
	virtual void enable(LightIndex lightIndex)=0;

	//glDisable  (LIGHTn override)
	virtual void disable(LightIndex lightIndex)=0;

	//glEnable (texture override)
	virtual void enable(TexTarget texTarget)=0;

	//glDisable (texture override)
	virtual void disable(TexTarget texTarget)=0;

	virtual ~Context();

	static Context&  getInstance();

     protected:

	static void setInstance(Context * instance);

     private:

	static Context *_instance;

     };
	
} /* my_gl */



#endif /* end of include guard: CONTEXT_HPP */
