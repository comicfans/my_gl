/*
 * =====================================================================================
 *
 *       Filename:  Export.cpp
 *
 *    Description:  export function through Context
 *
 *        Version:  1.0
 *        Created:  2011-11-9 16:49:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Export.hpp"

#include <cassert>
#include <cmath>

#include "Context.hpp"

using namespace my_gl;

using std::nearbyint;

#ifdef __cplusplus

extern "C"
{


  void    glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
     return Context::getInstance().clearColor(red,green,blue,alpha);
}


  void   glClear( GLbitfield mask )
{
     FrameBufferMask internalMask=0;

     if (mask&GL_COLOR_BUFFER_BIT)
     {
	  internalMask|=COLOR_BUFFER_BIT;
     }
     if (mask&GL_DEPTH_BUFFER_BIT)
     {
	  internalMask|=DEPTH_BUFFER_BIT;
     }
     Context::getInstance().clear(internalMask);
}

  void   glCullFace( GLenum mode )
{
     Context::getInstance().cullFace(mode);
}


  void   glFrontFace( GLenum mode )
{

     Context::getInstance().frontFace(mode);
}


  void   glEnable( GLenum cap )
{
     Context::getInstance().enable(cap);
}

  void   glDisable( GLenum cap )
{

     Context::getInstance().disable(cap);
}



  void   glEnableClientState( GLenum cap )  /* 1.1 */
{
     Context::getInstance().enableClientState(cap);
}

  void   glDisableClientState( GLenum cap )  /* 1.1 */
{
     Context::getInstance().disableClientState(cap);

}


  void    glFlush( void )
{
     Context::getInstance().flush();
}


  void    glClearDepth( GLclampd depth )
{
     Context::getInstance().clearDepth(depth);
}




  void   glDepthRange( GLclampd near_val, GLclampd far_val )
{
     Context::getInstance().depthRange(near_val,far_val);
}


  void   glMatrixMode( GLenum mode )
{
     Context::getInstance().matrixMode(mode);
}

  void   glOrtho( GLdouble left, GLdouble right, 
	  GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val )
{

     Context::getInstance().ortho(left,right,bottom,top,near_val,far_val);
}


  void   glFrustum( GLdouble left, GLdouble right, 
	  GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val )
{
     Context::getInstance().frustum(left,right,bottom,top,near_val,far_val);
}

  void   glViewport( GLint x, GLint y, GLsizei width, GLsizei height )
{
     Context::getInstance().viewport(x,y,width,height);
}
  void   glPushMatrix( void )
{
     Context::getInstance().pushMatrix();
}

  void   glPopMatrix( void )
{
     Context::getInstance().popMatrix();
}

  void   glLoadIdentity( void )
{
     Context::getInstance().loadIdentity();
}

  void   glLoadMatrixf( const GLfloat *m )
{
     Context::getInstance().loadMatrixf(m);
}

  void   glMultMatrixf( const GLfloat *m )
{
     Context::getInstance().multMatrixf(m);
}

  void   glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
     Context::getInstance().rotatef(angle,x,y,z);
}

  void   glScalef( GLfloat x, GLfloat y, GLfloat z )
{
     Context::getInstance().scalef(x,y,z);
}

  void   glTranslatef( GLfloat x, GLfloat y, GLfloat z )
{
     Context::getInstance().translatef(x,y,z);
}
  void   glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz )
{
     Context::getInstance().normal3f(nx,ny,nz);
}
  void   glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
     Context::getInstance().color4f(red,green,blue,alpha);
}


  void   glLightModelf( GLenum pname, GLfloat param )
{
     Context::getInstance().lightModelf(GL_LIGHT_MODEL_TWO_SIDE,param);
}

  void   glLightModelfv( GLenum pname, const GLfloat *params )
{
     Context::getInstance().lightModelfv(GL_AMBIENT,params);
}

  void   glMaterialf( GLenum face, GLenum pname, GLfloat param )
{
     Context::getInstance().materialf
	  (GL_FRONT_AND_BACK,GL_SHININESS,param);
}


  void   glMaterialfv( GLenum face, GLenum pname, const GLfloat *params )
{
     Context::getInstance().materialfv(GL_FRONT_AND_BACK,
	       pname,params);
}


  void   glLightf( GLenum light, GLenum pname, GLfloat param )
{
     Context::getInstance().lightf(light,pname,param);
}

  void   glLightfv( GLenum light, GLenum pname, const GLfloat *params )
{
     Context::getInstance().lightfv(light,pname,params);
}
     


  void   glTexImage2D( GLenum target, GLint level, 
	  GLenum internalFormat, 
	  GLsizei width, GLsizei height, 
	  GLint border, GLenum format, GLenum type, const GLvoid *pixels )
{
     assert(internalFormat==GL_RGB || internalFormat==GL_RGBA);

     Context::getInstance().texImage2D(GL_TEXTURE_2D,level,
	       int(internalFormat),
	       width,height,border,format,
	       GL_UNSIGNED_BYTE,pixels);
}
  void   glDeleteTextures( GLsizei n, const GLuint *textures)
{
     Context::getInstance().deleteTextures(n,textures);
}
  void   glBindTexture( GLenum target, GLuint texture )
{
     Context::getInstance().bindTexture(GL_TEXTURE_2D,texture);
}

  void   glTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, 
	  GLsizei width, GLsizei height, 
	  GLenum format, GLenum type, const GLvoid *pixels )
{

     Context::getInstance().texSubImage2D(GL_TEXTURE_2D,level,
	       xoffset,yoffset,width,height,format,
	       type,pixels);
}

  GLboolean   glIsTexture( GLuint texture )
{
     return Context::getInstance().isTexture(texture);
}

  void   glCopyTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, GLint x, GLint y, 
	  GLsizei width, GLsizei height )
{
     Context::getInstance().copyTexSubImage2D(GL_TEXTURE_2D,level,
	       xoffset,yoffset,x,y,width,height);
}

  void   glCopyTexImage2D( GLenum target, GLint level, 
	  GLenum internalformat, GLint x, GLint y, 
	  GLsizei width, GLsizei height, GLint border )
{
     Context::getInstance().copyTexImage2D(GL_TEXTURE_2D,level,
	       internalformat,x,y,width,height,border);
}

  void   glVertexPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().vertexPointer(size,type,stride,ptr);

}
  void   glNormalPointer( GLenum type, GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().normalPointer(type,stride,ptr);
}
  void   glColorPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().colorPointer(size,type,stride,ptr);
}

  void   glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().texCoordPointer(size,type,stride,ptr);
}

  void   glDrawArrays( GLenum mode, GLint first, GLsizei count )
{
     Context::getInstance().drawArrays(mode,first,count);
}

  void   glDrawElements( GLenum mode, GLsizei count, 
	  GLenum type, const GLvoid *indices )
{
     Context::getInstance().drawElements(mode,count,
	       type,indices);
}
     

  void   glBindBuffer (GLenum target, GLuint buffer)
{
     Context::getInstance().bindBuffer(target,buffer);
}
  void   glDeleteBuffers (GLsizei n, const GLuint *buffers)
{
     Context::getInstance().deleteBuffers(n,buffers);
}

  void   glGenBuffers (GLsizei n, GLuint *buffers)
{
     Context::getInstance().genBuffers(n,buffers);
}
  GLboolean   glIsBuffer (GLuint buffer)
{
     return Context::getInstance().isBuffer(buffer);

}

  void   glBufferData 
(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{

     //TODO no data usage map
     Context::getInstance().bufferData(target,
	       size,data,GL_STATIC_DRAW);
}

  void   glBufferSubData 
(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{

     Context::getInstance().bufferSubData(target,
	       offset,size,data);
}

  void   glTexEnvf( GLenum target, GLenum pname, GLfloat param )
{

     int nearby=nearbyint(param);

     Context::getInstance().texEnvf(0,0,nearby);

}

  void   glTexParameteri( GLenum target, GLenum pname, GLenum param )
{


     auto& context=Context::getInstance();

     context.texParameteri(GL_TEXTURE_2D,pname,param);

}
  void   glGenTextures( GLsizei n, GLuint *textures )
{
     Context::getInstance().genTextures(n,textures);
}
}

#endif
