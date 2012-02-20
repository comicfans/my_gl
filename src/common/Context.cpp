/*
 * =====================================================================================
 *
 *       Filename:  Context.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-21 14:26:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Context.hpp"

#include <cassert>
namespace my_gl {
     Context::~Context(){}

     Context *Context::_instance;

     Context&  Context::getInstance()
     {
	  assert(_instance);
	  return *_instance;
     }

     void Context::setInstance(Context * instance)
     {
	  _instance=instance;
     }

     void Context::enable(GLenum cap)
     {
	  if (cap>=GL_LIGHT0 && cap<= GL_LIGHT7)
	  {
	       enableLightN(cap);
	       return;
	  }

	  switch(cap)
	  {
	       case GL_LIGHTING:
		    enableLighting();
		    return;
	       case GL_TEXTURE_2D:
		    enableTexTarget(GL_TEXTURE_2D);
		    return;
	       case GL_CULL_FACE:
		    enableCullFace();
		    return;
	       case GL_NORMALIZE:
		    enableNormal(GL_NORMALIZE);
		    return;
	       case GL_RESCALE_NORMAL:
		    enableNormal(GL_RESCALE_NORMAL);
		    return;
	       default:
		    {
			 assert(false);
		    }
	  }

     }

     void Context::disable(GLenum cap)
     {
	  if (cap>=GL_LIGHT0 && cap<= GL_LIGHT7)
	  {
	       disableLightN(cap);
	       return;
	  }

	  switch(cap)
	  {
	       case GL_LIGHTING:
		    disableLighting();
		    return;
	       case GL_TEXTURE_2D:
		    disableTexTarget(GL_TEXTURE_2D);
		    return;
	       case GL_CULL_FACE:
		    disableCullFace();
		    return;
	       case GL_NORMALIZE:
		    disableNormal(GL_NORMALIZE);
		    return;
	       case GL_RESCALE_NORMAL:
		    disableNormal(GL_RESCALE_NORMAL);
		    return;
	       default:
		    {
			 assert(false);
		    }
	  }


     }

} /* my_gl */
