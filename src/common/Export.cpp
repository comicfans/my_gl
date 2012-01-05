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
     struct EnumHash{

	  size_t operator()(const GLenum glEnum) const
	  {
	       std::hash<int> hasher;

	       return hasher.operator()(int(glEnum));
	  }

     };


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
     static unordered_map<GLenum,Face,EnumHash> map={
	  {GL_FRONT,Face::FRONT},
	  {GL_BACK,Face::BACK},
	  {GL_FRONT_AND_BACK,Face::FRONT_AND_BACK}};

     Context::getInstance().cullFace(map[mode]);

}


  void   glFrontFace( GLenum mode )
{
     static unordered_map<GLenum,FaceMode,EnumHash> map=
     {{GL_CW,FaceMode::CW},{GL_CCW,FaceMode::CCW}};

     Context::getInstance().frontFace(map[mode]);
}

static unordered_map<GLenum,LightIndex,EnumHash> LIGHT_INDEX_MAP={
     {GL_LIGHT0,LightIndex::LIGHT0},{GL_LIGHT1,LightIndex::LIGHT1},
     {GL_LIGHT2,LightIndex::LIGHT2},{GL_LIGHT3,LightIndex::LIGHT3},
     {GL_LIGHT4,LightIndex::LIGHT4},{GL_LIGHT5,LightIndex::LIGHT5},
     {GL_LIGHT6,LightIndex::LIGHT6},{GL_LIGHT7,LightIndex::LIGHT7}};

  void   glEnable( GLenum cap )
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

  void   glDisable( GLenum cap )
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


static unordered_map<GLenum,BindState,EnumHash> BIND_STATE_MAP={
     {GL_VERTEX_ARRAY,BindState::VERTEX},{GL_COLOR_ARRAY,BindState::COLOR},
     {GL_NORMAL_ARRAY,BindState::NORMAL},{GL_TEXTURE_COORD_ARRAY,BindState::TEXCOORD}};

  void   glEnableClientState( GLenum cap )  /* 1.1 */
{
     Context::getInstance().enableClientState(BIND_STATE_MAP[cap]);
}

  void   glDisableClientState( GLenum cap )  /* 1.1 */
{
     Context::getInstance().disableClientState(BIND_STATE_MAP[cap]);

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
     static unordered_map<GLenum,MatrixMode,EnumHash> map={
	  {GL_MODELVIEW,MatrixMode::MODEL_VIEW},
	  {GL_PROJECTION,MatrixMode::PROJECTION},
	  {GL_TEXTURE,MatrixMode::TEXTURE}};

     Context::getInstance().matrixMode(map[mode]);
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
     Context::getInstance().lightModelf(LightParamName::TWO_SIDE,param);
}

  void   glLightModelfv( GLenum pname, const GLfloat *params )
{
     Context::getInstance().lightModelfv(LightParamName::AMBIENT,params);
}

  void   glMaterialf( GLenum face, GLenum pname, GLfloat param )
{
     Context::getInstance().materialf
	  (Face::FRONT_AND_BACK,LightParamName::SHININESS,param);
}

static   unordered_map<GLenum,LightParamName,EnumHash> COMMON_LIGHT_MAP={
	  {GL_AMBIENT,LightParamName::AMBIENT},
	  {GL_DIFFUSE,LightParamName::DIFFUSE},
	  {GL_SPECULAR,LightParamName::SPECULAR},
	  {GL_EMISSION,LightParamName::EMISSION},
	  {GL_AMBIENT_AND_DIFFUSE,LightParamName::AMBIENT_AND_DIFFUSE}};


  void   glMaterialfv( GLenum face, GLenum pname, const GLfloat *params )
{
     Context::getInstance().materialfv(Face::FRONT_AND_BACK,
	       COMMON_LIGHT_MAP[pname],params);
}

unordered_map<GLenum,LightParamName,EnumHash> staticInitLightMap()
{
     auto ret=COMMON_LIGHT_MAP;

     ret[GL_POSITION]=LightParamName::POSITION;
     ret[GL_SPOT_DIRECTION]=LightParamName::SPOT_DIRECTION;

     return ret;
}

  void   glLightf( GLenum light, GLenum pname, GLfloat param )
{
     static unordered_map<GLenum,LightParamName,EnumHash> map={
	  {GL_SPOT_EXPONENT,LightParamName::SPOT_EXPONENT},
	  {GL_SPOT_CUTOFF,LightParamName::SPOT_CUTOFF},
	  {GL_CONSTANT_ATTENUATION,LightParamName::CONSTANT_ATTENUATION},
	  {GL_LINEAR_ATTENUATION,LightParamName::LINEAR_ATTENUATION},
	  {GL_QUADRATIC_ATTENUATION,LightParamName::QUADRATIC_ATTENUATION}};

     Context::getInstance().lightf(LIGHT_INDEX_MAP[light],map[pname],param);
}

  void   glLightfv( GLenum light, GLenum pname, const GLfloat *params )
{
     static unordered_map<GLenum,LightParamName,EnumHash> map=staticInitLightMap();

     Context::getInstance().lightfv(LIGHT_INDEX_MAP[light],map[pname],params);
}
     
static unordered_map<GLenum,ImageFormat,EnumHash> IMAGE_FORMAT_MAP={
	  {GL_RGB,ImageFormat::RGB},
	  {GL_RGBA,ImageFormat::RGBA}};


  void   glTexImage2D( GLenum target, GLint level, 
	  GLenum internalFormat, 
	  GLsizei width, GLsizei height, 
	  GLint border, GLenum format, GLenum type, const GLvoid *pixels )
{
     assert(internalFormat==GL_RGB || internalFormat==GL_RGBA);

     Context::getInstance().texImage2D(TexTarget::TEXTURE_2D,level,
	       int(IMAGE_FORMAT_MAP[internalFormat]),
	       width,height,border,IMAGE_FORMAT_MAP[format],
	       StoreType::UNSIGNED_BYTE,pixels);
}
  void   glDeleteTextures( GLsizei n, const GLuint *textures)
{
     Context::getInstance().deleteTextures(n,textures);
}
  void   glBindTexture( GLenum target, GLuint texture )
{
     Context::getInstance().bindTexture(TexTarget::TEXTURE_2D,texture);
}

  void   glTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, 
	  GLsizei width, GLsizei height, 
	  GLenum format, GLenum type, const GLvoid *pixels )
{

     Context::getInstance().texSubImage2D(TexTarget::TEXTURE_2D,level,
	       xoffset,yoffset,width,height,IMAGE_FORMAT_MAP[format],
	       StoreType::UNSIGNED_BYTE,pixels);
}

  GLboolean   glIsTexture( GLuint texture )
{
     return Context::getInstance().isTexture(texture);
}

  void   glCopyTexSubImage2D( GLenum target, GLint level, 
	  GLint xoffset, GLint yoffset, GLint x, GLint y, 
	  GLsizei width, GLsizei height )
{
     Context::getInstance().copyTexSubImage2D(TexTarget::TEXTURE_2D,level,
	       xoffset,yoffset,x,y,width,height);
}

  void   glCopyTexImage2D( GLenum target, GLint level, 
	  GLenum internalformat, GLint x, GLint y, 
	  GLsizei width, GLsizei height, GLint border )
{
     Context::getInstance().copyTexImage2D(TexTarget::TEXTURE_2D,level,
	       IMAGE_FORMAT_MAP[internalformat],x,y,width,height,border);
}

static unordered_map<GLenum,DataType,EnumHash> DATA_TYPE_MAP={
     {GL_BYTE,DataType::BYTE},
     {GL_UNSIGNED_BYTE,DataType::UNSIGNED_BYTE},
     {GL_FLOAT,DataType::FLOAT},
     {GL_SHORT,DataType::SHORT},
     {GL_UNSIGNED_SHORT,DataType::UNSIGNED_SHORT}};

  void   glVertexPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().vertexPointer(size,DATA_TYPE_MAP[type],stride,ptr);

}
  void   glNormalPointer( GLenum type, GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().normalPointer(DATA_TYPE_MAP[type],stride,ptr);
}
  void   glColorPointer( GLint size, GLenum type, 
	  GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().colorPointer(size,DATA_TYPE_MAP[type],stride,ptr);
}

  void   glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *ptr )
{
     Context::getInstance().texCoordPointer(size,DATA_TYPE_MAP[type],stride,ptr);
}

static unordered_map<GLenum,PrimitiveMode,EnumHash> PRIMITIVE_MODE_MAP={
     {GL_POINTS,PrimitiveMode::POINTS},
     {GL_LINES,PrimitiveMode::LINES},
     {GL_LINE_STRIP,PrimitiveMode::LINE_STRIP},
     {GL_LINE_LOOP,PrimitiveMode::LINE_LOOP},
     {GL_TRIANGLES,PrimitiveMode::TRIANGLES},
     {GL_TRIANGLE_STRIP,PrimitiveMode::TRIANGLE_STRIP},
     {GL_TRIANGLE_FAN,PrimitiveMode::TRIANGLE_FAN}};

  void   glDrawArrays( GLenum mode, GLint first, GLsizei count )
{
     Context::getInstance().drawArrays(PRIMITIVE_MODE_MAP[mode],first,count);
}

  void   glDrawElements( GLenum mode, GLsizei count, 
	  GLenum type, const GLvoid *indices )
{
     Context::getInstance().drawElements(PRIMITIVE_MODE_MAP[mode],count,
	       DATA_TYPE_MAP[type],indices);
}
     
     static unordered_map<GLenum,BufferTarget,EnumHash> BUFFER_TARGET_MAP={
	  {GL_ELEMENT_ARRAY_BUFFER,BufferTarget::ELEMENT_ARRAY_BUFFER},
	  {GL_ARRAY_BUFFER,BufferTarget::ARRAY_BUFFER}};

  void   glBindBuffer (GLenum target, GLuint buffer)
{
     Context::getInstance().bindBuffer(BUFFER_TARGET_MAP[target],buffer);
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
     Context::getInstance().bufferData(BUFFER_TARGET_MAP[target],
	       size,data,DataUsage::STATIC_DRAW);
}

  void   glBufferSubData 
(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{

     Context::getInstance().bufferSubData(BUFFER_TARGET_MAP[target],
	       offset,size,data);
}

  void   glTexEnvf( GLenum target, GLenum pname, GLfloat param )
{
     static unordered_map<int,TexEnvMode> ENV_MODE_MAP={
	  {GL_REPLACE,TexEnvMode::REPLACE},
	  {GL_MODULATE,TexEnvMode::MODULATE},
	  {GL_DECAL,TexEnvMode::DECAL}};

     int nearby=nearbyint(param);

     Context::getInstance().texEnvf(0,0,ENV_MODE_MAP[nearby]);

}

  void   glTexParameteri( GLenum target, GLenum pname, GLenum param )
{

     static unordered_map<GLenum,TexWrapName,EnumHash> WRAP_NAME_MAP={
	  {GL_TEXTURE_WRAP_S,TexWrapName::TEXTURE_WRAP_S},
	  {GL_TEXTURE_WRAP_T,TexWrapName::TEXTURE_WRAP_T}};

     static unordered_map<GLenum,TexWrapMode,EnumHash> WRAP_MODE_MAP={
	  {GL_CLAMP,TexWrapMode::CLAMP},
	  {GL_REPEAT,TexWrapMode::REPEAT},
	  {GL_MIRRORED_REPEAT,TexWrapMode::MIRRORED_REPEAT}};

     static unordered_map<GLenum,TexFilterName,EnumHash> FILTER_NAME_MAP={
	  {GL_TEXTURE_MIN_FILTER,TexFilterName::TEXTURE_MIN_FILTER},
	  {GL_TEXTURE_MAG_FILTER,TexFilterName::TEXTURE_MAG_FILTER}};

     static unordered_map<GLenum,TexFilterMode,EnumHash> FILTER_MODE_MAP={
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
  void   glGenTextures( GLsizei n, GLuint *textures )
{
     Context::getInstance().genTextures(n,textures);
}
}

#endif
