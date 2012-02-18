/*
 * =====================================================================================
 *
 *       Filename:  NormalManager.hpp
 *
 *    Description:  class to manager normal provider
 *    		    normal is just a Vec3, but for making 
 *    		    interface the same, use Vec4 instead
 *
 *        Version:  1.0
 *        Created:  2011-9-19 15:51:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef NORMAL_MANAGER_HPP

#define NORMAL_MANAGER_HPP

#include <memory>

#include "TwoSourceVec4Manager.hpp"

namespace my_gl{

     class NormalManager :public TwoSourceVec4Manager{
     public:

	  NormalManager();

	  //glNormal3f
	  void normal3f(float nx,float ny,float nz);

	  //glNormalPointer
	  void normalPointer(GLenum type,size_t stride,
		    const void* pointer);

	  static const GLenum BIND_STATE=GL_NORMAL_ARRAY;

     };
	
} /* my_gl */


#endif /* end of include guard: NORMAL_MANAGER_HPP */
