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

#include <unordered_map>

#include "Context.hpp"

using namespace my_gl;

using std::unordered_map;

GLAPI void  APIENTRY glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
     return Context::getInstance().clearColor(red,green,blue,alpha);
}


GLAPI void APIENTRY glClear( GLbitfield mask )
{
     FrameBufferMask internalMask=0;

     if (mask&GL_COLOR_BUFFER_BIT)
     {
	  internalMask&=COLOR_BUFFER_BIT;
     }
     if (mask&GL_DEPTH_BUFFER_BIT)
     {
	  internalMask&=DEPTH_BUFFER_BIT;
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
	  case GL_TEXTURE:
	       context.enable(TexTarget::TEXTURE_2D);
	       return;
	  case GL_CULL_FACE:
	       context.enableCullFace();
	       return;
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
	  case GL_TEXTURE:
	       context.disable(TexTarget::TEXTURE_2D);
	       return;
	  case GL_CULL_FACE:
	       context.disableCullFace();
	       return;
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
