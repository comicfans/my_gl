/*
 * =====================================================================================
 *
 *       Filename:  MaterialParam.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 23:54:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "MaterialParam.hpp"

#include <cassert>

namespace my_gl {

     MaterialParam::MaterialParam()
     {
	  //OpenGL spec default value
	  emission=Vec4(0,0,0,1);
	  ambient=Vec4(0.2,0.2,0.2,1);
	  diffuse=Vec4(0.8,0.8,0.8,1);
	  specular=Vec4(0,0,0,1);
	  shininess=0;
     }

     void MaterialParam::materialf
	  (GLenum /*ignore*/,GLenum paramName,float param)
	  {
	       assert(paramName==GL_SHININESS);

	       shininess=param;
	  }

     void MaterialParam::materialfv
	  (GLenum /*ignore*/,GLenum paramName,const float* param)
	  {
	       switch (paramName)
	       {
		    case GL_AMBIENT:
			 ambient=param;
			 break;
		    case GL_DIFFUSE:
			 diffuse=param;
			 break;
		    case GL_SPECULAR:
			 specular=param;
			 break;
		    case GL_EMISSION:
			 emission=param;
			 break;
		    case GL_AMBIENT_AND_DIFFUSE:
			 ambient=diffuse=param;
			 break;
		    default:
			 {
			      assert(false);
			 }
	       }
	  }

} /* my_gl */
