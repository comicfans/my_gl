/*
 * =====================================================================================
 *
 *       Filename:  Export.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-5 10:56:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ();, 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef EXPORT_HPP

#define EXPORT_HPP

#include <cstddef>
#ifdef __cplusplus

extern "C"
{


typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

enum GLenum{
     GL_STATIC_DRAW,

     GL_COLOR_BUFFER_BIT,
     GL_DEPTH_BUFFER_BIT,

     GL_FRONT,
     GL_BACK,
     GL_FRONT_AND_BACK,

     GL_CW,
     GL_CCW,

     GL_LIGHTING,

     GL_LIGHT0,
     GL_LIGHT1,
     GL_LIGHT2,
     GL_LIGHT3,
     GL_LIGHT4,
     GL_LIGHT5,
     GL_LIGHT6,
     GL_LIGHT7,

     GL_DECAL,
     GL_MODULATE,
     GL_REPLACE,


     GL_VERTEX_ARRAY,
     GL_NORMAL_ARRAY,
     GL_TEXTURE_COORD_ARRAY,
     GL_COLOR_ARRAY,

     GL_MODELVIEW,
     GL_PROJECTION,

     GL_NEAREST,
     GL_LINEAR,

     GL_CULL_FACE,

     GL_NORMALIZE,
     GL_RESCALE_NORMAL,

     GL_TEXTURE_2D,
     GL_TEXTURE,
     GL_TEXTURE_ENV,
     GL_TEXTURE_ENV_MODE,

     GL_TEXTURE_WRAP_S,
     GL_TEXTURE_WRAP_T,

     GL_TEXTURE_MIN_FILTER,
     GL_MIRRORED_REPEAT,
     GL_CLAMP,
     GL_REPEAT,
     GL_TEXTURE_MAG_FILTER,

     GL_POSITION,
     GL_AMBIENT,
     GL_EMISSION,
     GL_DIFFUSE,
     GL_AMBIENT_AND_DIFFUSE,
     GL_SPECULAR,
     GL_SPOT_DIRECTION,
     GL_SPOT_EXPONENT,
     GL_SPOT_CUTOFF,
     GL_LINEAR_ATTENUATION,
     GL_CONSTANT_ATTENUATION,
     GL_SHININESS,
     GL_LIGHT_MODEL_AMBIENT,
     GL_QUADRATIC_ATTENUATION,

     GL_RGB,
     GL_RGBA,

     GL_POINTS,
     GL_LINES,
     GL_LINE_STRIP,
     GL_LINE_LOOP,
     GL_TRIANGLES,
     GL_TRIANGLE_STRIP,
     GL_TRIANGLE_FAN,

     GL_BYTE,
     GL_SHORT,
     GL_FLOAT,
     GL_UNSIGNED_BYTE,
     GL_UNSIGNED_SHORT,

     GL_ARRAY_BUFFER,
     GL_ELEMENT_ARRAY_BUFFER
};

  void    glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
  void   glClear( GLbitfield mask );
  void   glCullFace( GLenum mode );
  void   glFrontFace( GLenum mode );
  void   glEnable( GLenum cap );
  void   glDisable( GLenum cap );
  void   glEnableClientState( GLenum cap );  /* 1.1 */
  void   glDisableClientState( GLenum cap );  /* 1.1 */
  void    glFlush( void );
  void    glClearDepth( GLclampd depth );
  void   glDepthRange( GLclampd near_val, GLclampd far_val );
  void   glDepthRange( GLclampd near_val, GLclampd far_val );
  void   glOrtho( GLdouble left, GLdouble right, 
	  GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val );
  void   glFrustum( GLdouble left, GLdouble right, 
	  GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val );
  void   glViewport( GLint x, GLint y, GLsizei width, GLsizei height );
  void   glPushMatrix( void );
  void   glPopMatrix( void );
  void   glLoadIdentity( void );
  void   glLoadMatrixf( const GLfloat *m );

  void   glMultMatrixf( const GLfloat *m );
  void   glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z );
  void   glScalef( GLfloat x, GLfloat y, GLfloat z );
  void   glTranslatef( GLfloat x, GLfloat y, GLfloat z );
  void   glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz );
  void   glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
  void   glLightModelf( GLenum pname, GLfloat param );
  void   glMaterialf( GLenum face, GLenum pname, GLfloat param );
  void   glMaterialfv( GLenum face, GLenum pname, const GLfloat *params );
  void   glLightf( GLenum light, GLenum pname, GLfloat param );
  void   glLightfv( GLenum light, GLenum pname, const GLfloat *params );
  void   glLightModelfv( GLenum pname, const GLfloat *params );
  void   glTexImage2D( GLenum target, GLint level, 
	  GLenum internalFormat, 
	  GLsizei width, GLsizei height, 
	  GLint border, GLenum format, GLenum type, const GLvoid *pixels );
  void   glDeleteTextures( GLsizei n, const GLuint *textures);
  void   glBindTexture( GLenum target, GLuint texture );
  void   glTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, 
	  GLsizei width, GLsizei height, 
	  GLenum format, GLenum type, const GLvoid *pixels );
  GLboolean   glIsTexture( GLuint texture );
  void   glCopyTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, GLint x, GLint y, 
	  GLsizei width, GLsizei height );
  void   glCopyTexImage2D( GLenum target, GLint level, 
	  GLenum internalformat, GLint x, GLint y, 
	  GLsizei width, GLsizei height, GLint border );
  void   glVertexPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr );
  void   glNormalPointer( GLenum type, GLsizei stride, const GLvoid *ptr );
  void   glColorPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr );
  void   glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *ptr );
  void   glDrawArrays( GLenum mode, GLint first, GLsizei count );
  void   glDrawElements( GLenum mode, GLsizei count, 
	  GLenum type, const GLvoid *indices );
  void   glBindBuffer (GLenum target, GLuint buffer);
  void   glDeleteBuffers (GLsizei n, const GLuint *buffers);
  void   glGenBuffers (GLsizei n, GLuint *buffers);
  GLboolean   glIsBuffer (GLuint buffer);
  void   glBufferData 
(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
  void   glBufferSubData 
(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
  void   glTexEnvf( GLenum target, GLenum pname, GLfloat param );
  void   glTexParameteri( GLenum target, GLenum pname, GLenum param );
  void   glGenTextures( GLsizei n, GLuint *textures );
  void   glMatrixMode( GLenum mode );
};


#endif//extern c
#endif /* end of include guard: EXPORT_HPP */
