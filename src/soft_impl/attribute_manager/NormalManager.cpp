/*
 * =====================================================================================
 *
 *       Filename:  NormalManager.cpp
 *
 *    Description:  implementation of NormalManager
 *
 *        Version:  1.0
 *        Created:  2011-9-19 16:00:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "NormalManager.hpp"

#include <cassert>

#include "common/UniqueVec4Provider.hpp"

namespace my_gl {

     // GL Client Normal Array is Disabled by default
     NormalManager::NormalManager()
	  :TwoSourceVec4Manager(BIND_STATE)
     {
	  //default value of normal ,see reference manual
	  setValue(Vec4{0,0,1,0});
     }

     void NormalManager::normal3f(float nx,float ny,float nz)
     {
	  //TODO 
	  //if normal array is enabled ,what behavie is defined 
	  //when glNormal3f is called?
	  //currently only assert false;

	  assert(!vertexArrayEnabled());

	  setValue(Vec4{nx,ny,nz});

     }

     void NormalManager::normalPointer(DataType type,
	       size_t stride, const void *pointer)
     {
	  vertexArrayChange(3,type,stride,pointer);
     }


} /* my_gl */
