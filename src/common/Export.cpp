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

#include <GL/gl.h>
#include <GL/glext.h>

#include <cassert>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

#include "Context.hpp"

using namespace my_gl;

using std::unordered_map;
using std::unordered_set;
using std::nearbyint;

#ifdef __cplusplus

extern "C"
{

GLAPI void  APIENTRY glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
     return Context::getInstance().clearColor(red,green,blue,alpha);
}


GLAPI void APIENTRY glClear( GLbitfield mask )
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

GLAPI void APIENTRY glCullFace( GLenum mode )
{
     static unordered_map<GLenum,Face> map={
	  {GL_FRONT,Face::FRONT},
	  {GL_BACK,Face::BACK},
	  {GL_FRONT_AND_BACK,Face::FRONT_AND_BACK}};

     Context::getInstance().cullFace(map[mode]);

}


GLAPI void APIENTRY glFrontFace( GLenum mode )
{
     static unordered_map<GLenum,FaceMode> map=
     {{GL_CW,FaceMode::CW},{GL_CCW,FaceMode::CCW}};

     Context::getInstance().frontFace(map[mode]);
}

static unordered_map<GLenum,LightIndex> LIGHT_INDEX_MAP={
     {GL_LIGHT0,LightIndex::LIGHT0},{GL_LIGHT1,LightIndex::LIGHT1},
     {GL_LIGHT2,LightIndex::LIGHT2},{GL_LIGHT3,LightIndex::LIGHT3},
     {GL_LIGHT4,LightIndex::LIGHT4},{GL_LIGHT5,LightIndex::LIGHT5},
     {GL_LIGHT6,LightIndex::LIGHT6},{GL_LIGHT7,LightIndex::LIGHT7}};

GLAPI void APIENTRY glEnable( GLenum cap )
{
     Context& context=Context::getInstance();

     if (cap>=GL_LIGHT0 && cap<= GL_LIGHT7)
     {
	  context.enable(LIGHT_INDEX_MAP[cap]);
	  return;
     }

     switch(cap)
     {
	  case GL_LIGHTING:
	       context.enableLighting();
	       return;
	  case GL_TEXTURE_2D:
	       context.enable(TexTarget::TEXTURE_2D);
	       return;
	  case GL_CULL_FACE:
	       context.enableCullFace();
	       return;
	  case GL_NORMALIZE:
	       context.enable(NormalizeNormal::NORMALIZE);
	       return;
	  case GL_RESCALE_NORMAL:
	       context.enable(NormalizeNormal::RESCALE_NORMAL);
	       return;
	  default:
	       {
		    assert(false);
	       }
     }

}

GLAPI void APIENTRY glDisable( GLenum cap )
{

     Context& context=Context::getInstance();

     if (cap>=GL_LIGHT0 && cap<= GL_LIGHT7)
     {
	  context.disable(LIGHT_INDEX_MAP[cap]);
	  return;
     } 

     switch(cap)
     {
	  case GL_LIGHTING:
	       context.disableLighting();
	       return;
	  case GL_TEXTURE_2D:
	       context.disable(TexTarget::TEXTURE_2D);
	       return;
	  case GL_CULL_FACE:
	       context.disableCullFace();
	       return;
	  case GL_NORMALIZE:
	       context.disable(NormalizeNormal::NORMALIZE);
	       return;
	  case GL_RESCALE_NORMAL:
	       context.disable(NormalizeNormal::RESCALE_NORMAL);
	       return;
	  default:
	       {
		    assert(false);
	       }

     }
}


static unordered_map<GLenum,BindState> BIND_STATE_MAP={
     {GL_VERTEX_ARRAY,BindState::VERTEX},{GL_COLOR_ARRAY,BindState::COLOR},
     {GL_NORMAL_ARRAY,BindState::NORMAL},{GL_TEXTURE_COORD_ARRAY,BindState::TEXCOORD}};

GLAPI void APIENTRY glEnableClientState( GLenum cap )  /* 1.1 */
{
     Context::getInstance().enableClientState(BIND_STATE_MAP[cap]);
}

GLAPI void APIENTRY glDisableClientState( GLenum cap )  /* 1.1 */
{
     Context::getInstance().disableClientState(BIND_STATE_MAP[cap]);

}


GLAPI void  APIENTRY glFlush( void )
{
     Context::getInstance().flush();
}


GLAPI void  APIENTRY glClearDepth( GLclampd depth )
{
     Context::getInstance().clearDepth(depth);
}




GLAPI void APIENTRY glDepthRange( GLclampd near_val, GLclampd far_val )
{
     Context::getInstance().depthRange(near_val,far_val);
}


GLAPI void APIENTRY glMatrixMode( GLenum mode )
{
     static unordered_map<GLenum,MatrixMode> map={
	  {GL_MODELVIEW,MatrixMode::MODEL_VIEW},
	  {GL_PROJECTION,MatrixMode::PROJECTION},
	  {GL_TEXTURE,MatrixMode::TEXTURE}};

     Context::getInstance().matrixMode(map[mode]);
}

GLAPI void APIENTRY glOrtho( GLdouble left, GLdouble right, 
	  GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val )
{

     Context::getInstance().ortho(left,right,bottom,top,near_val,far_val);
}


GLAPI void APIENTRY glFrustum( GLdouble left, GLdouble right, 
	  GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val )
{
     Context::getInstance().frustum(left,right,bottom,top,near_val,far_val);
}

GLAPI void APIENTRY glViewport( GLint x, GLint y, GLsizei width, GLsizei height )
{
     Context::getInstance().viewport(x,y,width,height);
}
GLAPI void APIENTRY glPushMatrix( void )
{
     Context::getInstance().pushMatrix();
}

GLAPI void APIENTRY glPopMatrix( void )
{
     Context::getInstance().popMatrix();
}

GLAPI void APIENTRY glLoadIdentity( void )
{
     Context::getInstance().loadIdentity();
}

GLAPI void APIENTRY glLoadMatrixf( const GLfloat *m )
{
     Context::getInstance().loadMatrixf(m);
}

GLAPI void APIENTRY glMultMatrixf( const GLfloat *m )
{
     Context::getInstance().multMatrixf(m);
}

GLAPI void APIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
     Context::getInstance().rotatef(angle,x,y,z);
}

GLAPI void APIENTRY glScalef( GLfloat x, GLfloat y, GLfloat z )
{
     Context::getInstance().scalef(x,y,z);
}

GLAPI void APIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z )
{
     Context::getInstance().translatef(x,y,z);
}
GLAPI void APIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz )
{
     Context::getInstance().normal3f(nx,ny,nz);
}
GLAPI void APIENTRY glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
     Context::getInstance().color4f(red,green,blue,alpha);
}


GLAPI void APIENTRY glLightModelf( GLenum pname, GLfloat param )
{
     Context::getInstance().lightModelf(LightParamName::TWO_SIDE,param);
}

GLAPI void APIENTRY glLightModelfv( GLenum pname, const GLfloat *params )
{
     Context::getInstance().lightModelfv(LightParamName::AMBIENT,params);
}

GLAPI void APIENTRY glMaterialf( GLenum face, GLenum pname, GLfloat param )
{
     Context::getInstance().materialf
	  (Face::FRONT_AND_BACK,LightParamName::SHININESS,param);
}

static   unordered_map<GLenum,LightParamName> COMMON_LIGHT_MAP={
	  {GL_AMBIENT,LightParamName::AMBIENT},
	  {GL_DIFFUSE,LightParamName::DIFFUSE},
	  {GL_SPECULAR,LightParamName::SPECULAR},
	  {GL_EMISSION,LightParamName::EMISSION},
	  {GL_AMBIENT_AND_DIFFUSE,LightParamName::AMBIENT_AND_DIFFUSE}};


GLAPI void APIENTRY glMaterialfv( GLenum face, GLenum pname, const GLfloat *params )
{
     Context::getInstance().materialfv(Face::FRONT_AND_BACK,
	       COMMON_LIGHT_MAP[pname],params);
}

unordered_map<GLenum,LightParamName> staticInitLightMap()
{
     auto ret=COMMON_LIGHT_MAP;

     ret[GL_POSITION]=LightParamName::POSITION;
     ret[GL_SPOT_DIRECTION]=LightParamName::SPOT_DIRECTION;

     return ret;
}

GLAPI void APIENTRY glLightf( GLenum light, GLenum pname, GLfloat param )
{
     static unordered_map<GLenum,LightParamName> map={
	  {GL_SPOT_EXPONENT,LightParamName::SPOT_EXPONENT},
	  {GL_SPOT_CUTOFF,LightParamName::SPOT_CUTOFF},
	  {GL_CONSTANT_ATTENUATION,LightParamName::CONSTANT_ATTENUATION},
	  {GL_LINEAR_ATTENUATION,LightParamName::LINEAR_ATTENUATION},
	  {GL_QUADRATIC_ATTENUATION,LightParamName::QUADRATIC_ATTENUATION}};

     Context::getInstance().lightf(LIGHT_INDEX_MAP[light],map[pname],param);
}

GLAPI void APIENTRY glLightfv( GLenum light, GLenum pname, const GLfloat *params )
{
     static unordered_map<GLenum,LightParamName> map=staticInitLightMap();

     Context::getInstance().lightfv(LIGHT_INDEX_MAP[light],map[pname],params);
}
     
static unordered_map<GLenum,ImageFormat> IMAGE_FORMAT_MAP={
	  {GL_RGB,ImageFormat::RGB},
	  {GL_RGBA,ImageFormat::RGBA}};


GLAPI void APIENTRY glTexImage2D( GLenum target, GLint level, 
	  GLint internalFormat, 
	  GLsizei width, GLsizei height, 
	  GLint border, GLenum format, GLenum type, const GLvoid *pixels )
{
     assert(internalFormat==GL_RGB || internalFormat==GL_RGBA);

     Context::getInstance().texImage2D(TexTarget::TEXTURE_2D,level,
	       int(IMAGE_FORMAT_MAP[internalFormat]),
	       width,height,border,IMAGE_FORMAT_MAP[format],
	       StoreType::UNSIGNED_BYTE,pixels);
}
GLAPI void APIENTRY glDeleteTextures( GLsizei n, const GLuint *textures)
{
     Context::getInstance().deleteTextures(n,textures);
}
GLAPI void APIENTRY glBindTexture( GLenum target, GLuint texture )
{
     Context::getInstance().bindTexture(TexTarget::TEXTURE_2D,texture);
}

GLAPI void APIENTRY glTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, 
	  GLsizei width, GLsizei height, 
	  GLenum format, GLenum type, const GLvoid *pixels )
{

     Context::getInstance().texSubImage2D(TexTarget::TEXTURE_2D,level,
	       xoffset,yoffset,width,height,IMAGE_FORMAT_MAP[format],
	       StoreType::UNSIGNED_BYTE,pixels);
}

GLAPI GLboolean APIENTRY glIsTexture( GLuint texture )
{
     return Context::getInstance().isTexture(texture);
}

GLAPI void APIENTRY glCopyTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, GLint x, GLint y, 
	  GLsizei width, GLsizei height )
{
     Context::getInstance().copyTexSubImage2D(TexTarget::TEXTURE_2D,level,
	       xoffset,yoffset,x,y,width,height);
}

GLAPI void APIENTRY glCopyTexImage2D( GLenum target, GLint level, 
	  GLenum internalformat, GLint x, GLint y, 
	  GLsizei width, GLsizei height, GLint border )
{
     Context::getInstance().copyTexImage2D(TexTarget::TEXTURE_2D,level,
	       IMAGE_FORMAT_MAP[internalformat],x,y,width,height,border);
}

static unordered_map<GLenum,DataType> DATA_TYPE_MAP={
     {GL_BYTE,DataType::BYTE},
     {GL_UNSIGNED_BYTE,DataType::UNSIGNED_BYTE},
     {GL_FLOAT,DataType::FLOAT},
     {GL_SHORT,DataType::SHORT},
     {GL_UNSIGNED_SHORT,DataType::UNSIGNED_SHORT}};

GLAPI void APIENTRY glVertexPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().vertexPointer(size,DATA_TYPE_MAP[type],stride,ptr);

}
GLAPI void APIENTRY glNormalPointer( GLenum type, GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().normalPointer(DATA_TYPE_MAP[type],stride,ptr);
}
GLAPI void APIENTRY glColorPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().colorPointer(size,DATA_TYPE_MAP[type],stride,ptr);
}

GLAPI void APIENTRY glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().texCoordPointer(size,DATA_TYPE_MAP[type],stride,ptr);
}

static unordered_map<GLenum,PrimitiveMode> PRIMITIVE_MODE_MAP={
     {GL_POINTS,PrimitiveMode::POINTS},
     {GL_LINES,PrimitiveMode::LINES},
     {GL_LINE_STRIP,PrimitiveMode::LINE_STRIP},
     {GL_LINE_LOOP,PrimitiveMode::LINE_LOOP},
     {GL_TRIANGLES,PrimitiveMode::TRIANGLES},
     {GL_TRIANGLE_STRIP,PrimitiveMode::TRIANGLE_STRIP},
     {GL_TRIANGLE_FAN,PrimitiveMode::TRIANGLE_FAN}};

GLAPI void APIENTRY glDrawArrays( GLenum mode, GLint first, GLsizei count )
{
     Context::getInstance().drawArrays(PRIMITIVE_MODE_MAP[mode],first,count);
}

GLAPI void APIENTRY glDrawElements( GLenum mode, GLsizei count, 
	  GLenum type, const GLvoid *indices )
{
     Context::getInstance().drawElements(PRIMITIVE_MODE_MAP[mode],count,
	       DATA_TYPE_MAP[type],indices);
}
     
     static unordered_map<GLenum,BufferTarget> BUFFER_TARGET_MAP={
	  {GL_ELEMENT_ARRAY_BUFFER,BufferTarget::ELEMENT_ARRAY_BUFFER},
	  {GL_ARRAY_BUFFER,BufferTarget::ARRAY_BUFFER}};

GLAPI void APIENTRY glBindBuffer (GLenum target, GLuint buffer)
{
     Context::getInstance().bindBuffer(BUFFER_TARGET_MAP[target],buffer);
}
GLAPI void APIENTRY glDeleteBuffers (GLsizei n, const GLuint *buffers)
{
     Context::getInstance().deleteBuffers(n,buffers);
}

GLAPI void APIENTRY glGenBuffers (GLsizei n, GLuint *buffers)
{
     Context::getInstance().genBuffers(n,buffers);
}
GLAPI GLboolean APIENTRY glIsBuffer (GLuint buffer)
{
     return Context::getInstance().isBuffer(buffer);

}

GLAPI void APIENTRY glBufferData 
(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{

     //TODO no data usage map
     Context::getInstance().bufferData(BUFFER_TARGET_MAP[target],
	       size,data,DataUsage::STATIC_DRAW);
}

GLAPI void APIENTRY glBufferSubData 
(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{

     Context::getInstance().bufferSubData(BUFFER_TARGET_MAP[target],
	       offset,size,data);
}

GLAPI void APIENTRY glTexEnvf( GLenum target, GLenum pname, GLfloat param )
{
     static unordered_map<int,TexEnvMode> ENV_MODE_MAP={
	  {GL_REPLACE,TexEnvMode::REPLACE},
	  {GL_MODULATE,TexEnvMode::MODULATE},
	  {GL_DECAL,TexEnvMode::DECAL}};

     int nearby=nearbyint(param);

     Context::getInstance().texEnvf(0,0,ENV_MODE_MAP[nearby]);

}

GLAPI void APIENTRY glTexParameteri( GLenum target, GLenum pname, GLint param )
{

     static unordered_map<GLenum,TexWrapName> WRAP_NAME_MAP={
	  {GL_TEXTURE_WRAP_S,TexWrapName::TEXTURE_WRAP_S},
	  {GL_TEXTURE_WRAP_T,TexWrapName::TEXTURE_WRAP_T}};

     static unordered_map<GLenum,TexWrapMode> WRAP_MODE_MAP={
	  {GL_CLAMP,TexWrapMode::CLAMP},
	  {GL_REPEAT,TexWrapMode::REPEAT},
	  {GL_MIRRORED_REPEAT,TexWrapMode::MIRRORED_REPEAT}};

     static unordered_map<GLenum,TexFilterName> FILTER_NAME_MAP={
	  {GL_TEXTURE_MIN_FILTER,TexFilterName::TEXTURE_MIN_FILTER},
	  {GL_TEXTURE_MAG_FILTER,TexFilterName::TEXTURE_MAG_FILTER}};

     static unordered_map<GLenum,TexFilterMode> FILTER_MODE_MAP={
	  {GL_NEAREST,TexFilterMode::NEAREST},
	  {GL_LINEAR,TexFilterMode::LINEAR}};

     auto& context=Context::getInstance();

     switch (pname)
     {
	  case GL_TEXTURE_WRAP_S:
	       context.texParameteri(TexTarget::TEXTURE_2D,
			 WRAP_NAME_MAP[pname],WRAP_MODE_MAP[param]);
	       break;
	  case GL_TEXTURE_WRAP_T:
	       context.texParameteri(TexTarget::TEXTURE_2D,
			 WRAP_NAME_MAP[pname],WRAP_MODE_MAP[param]);
	       break;
	  case GL_TEXTURE_MIN_FILTER:
	       context.texParameteri(TexTarget::TEXTURE_2D,
			 FILTER_NAME_MAP[pname],FILTER_MODE_MAP[param]);
	       break;
	  case GL_TEXTURE_MAG_FILTER:
	       context.texParameteri(TexTarget::TEXTURE_2D,
			 FILTER_NAME_MAP[pname],FILTER_MODE_MAP[param]);
	       break;

	  default:
	       {
		    assert(false);
	       }

     }

}
GLAPI void APIENTRY glGenTextures( GLsizei n, GLuint *textures )
{
     Context::getInstance().genTextures(n,textures);
}
}

#endif
