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
	virtual void  deleteBuffers(size_t size,const Name *names)=0;
	//glIsBuffer
	virtual bool isBuffer(Name name) const =0;

	//glBindBuffer
	virtual void bindBuffer(GLenum target,Name name)=0;

	//glBufferData
	virtual void bufferData(GLenum target,size_t size,
		    const void* data, GLenum usage)=0;

	//glBufferSubData
	virtual void bufferSubData(GLenum target,ptrdiff_t offset,
		    size_t size,const void* data)=0;


	//glVertexPointer
	virtual void  vertexPointer(int componentSize,GLenum type, 
		  size_t stride, const void * pointer)=0;

	//glNormal3f
	virtual void  normal3f(float nx,float ny,float nz)=0;

	//glNormalPointer
	virtual void  normalPointer(GLenum type,
		  size_t stride,const void  *pointer)=0;
	//glColor4f
	virtual void  color4f(float red,float green,
		  float blue,float alpha) =0;

	//glColor4ub
	virtual void  color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) =0;

	//glColorPointer
	virtual void  colorPointer(int componentSize,GLenum type,
		  size_t stride,const void  *pointer)=0;

	//glTexCoordPointer
	virtual void  texCoordPointer(int componentSize, 
		  GLenum type, size_t stride, const void * pointer)=0;

	//glGLenum
	virtual void matrixMode(GLenum matrixMode)=0;

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
	virtual void enableClientState(GLenum bindState)=0;

	//glDisableClient
	virtual void disableClientState(GLenum bindState)=0;

	//glDrawArrays 
	virtual void drawArrays(GLenum primitiveMode,
		  int first,size_t count)=0;

	//glDrawElements 
	virtual void drawElements(GLenum primitiveMode,
		  size_t count,GLenum dataType,const void* indices)=0;

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
	virtual void depthFunc(GLenum func)=0;

	//glFrontFace
	virtual void frontFace(GLenum faceMode)=0;

	//glCullFace
	virtual void cullFace(GLenum face)=0;

	void enable(GLenum cap);
	void disable(GLenum cap);


	//glMaterialf
	virtual void materialf
	     (GLenum face,GLenum paramName,float param)=0;

	//glMaterialfv
	virtual void materialfv
	     (GLenum face,GLenum paramName,const float *param)=0;

	//glDeleteTexture
	virtual void deleteTextures(size_t n,const Name *names)=0;

	//glLightf
	virtual void lightf(GLenum lightIndex,
		  GLenum paramName,float param)=0;

	//glLightfv
	virtual void lightfv(GLenum lightIndex,
		  GLenum paramName,const float* param)=0;

	//glLightModelf
	virtual void lightModelf(GLenum paramName,float param)=0;

	//glLightModelfv
	virtual void lightModelfv(GLenum paramName,const float *param)=0;

	//glTexImage2D
	virtual void texImage2D(GLenum/*ignored*/,int level/* ignored*/
		  ,int internalFormat/*ignored*/,size_t width,
		  //OpenGL ES 1.0 border must be 0
		  size_t height,int border/* ignored */,
		  GLenum imageFormat,GLenum storeType,
		  const void *texels)=0;

	//glTexSubImage2D
	virtual void texSubImage2D(GLenum/*ignored*/,
		  int level/* ignored*/,
		  int xoffset,int yoffset,
		  size_t width,size_t height,
		  GLenum imageFormat,
		  GLenum storeType,
		  const void *texels)=0;

	//glCopyTexImage2D
	virtual void copyTexImage2D(GLenum /*ignored*/,int level/* ignored*/,
		  GLenum internalFormat,
		  int x,int y,size_t width,size_t height,int border)=0;
 
	//glCopyTexSubImage2D
	virtual void copyTexSubImage2D(
		  GLenum /*ignored*/,int level/* ignored*/,
		  int xoffset,int yoffset,
		  int x,int y,size_t width,size_t height)=0;

	//glGenTextures
	virtual void genTextures(size_t n,Name * names)=0;

	//glBindTexture
	virtual void bindTexture(GLenum/* ignored*/,Name texture)=0;

	//glIsTexture
	virtual bool isTexture(Name name)=0;
		
	virtual void texParameteri(GLenum target/*ignored*/,
		  GLenum pname,
		  GLenum value)=0;
	
	virtual void texEnvf(GLenum target/*ignored*/,
		  GLenum pname/* ignored*/,GLenum texEnvMode)=0;

	virtual ~Context();

	static Context&  getInstance();

     protected:

	static void setInstance(Context * instance);

	//glEnable (normlize override)
	virtual void enableNormal(GLenum normalizeNormal)=0;
	//glDisable (cullFace override)
	virtual void disableNormal(GLenum normalizeNormal)=0;

	//glEnable (cullFace override)
	virtual void enableCullFace()=0;
	//glDisable (cullFace override)
	virtual void disableCullFace()=0;
	
	//glEnable  (LIGHTn override)
	virtual void enableLightN(GLenum lightIndex)=0;
	//glDisable  (LIGHTn override)
	virtual void disableLightN(GLenum lightIndex)=0;

	//glEnable (texture override)
	virtual void enableTexTarget(GLenum texTarget)=0;
	//glDisable (texture override)
	virtual void disableTexTarget(GLenum texTarget)=0;

	//glEnable lighting
	virtual void enableLighting()=0;
	//glDisable lighting
	virtual void disableLighting()=0;

     private:

	static Context *_instance;

     };
	
} /* my_gl */



#endif /* end of include guard: CONTEXT_HPP */
