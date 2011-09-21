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

#include "common/UniqueVectorProvider.hpp"

namespace my_gl {

     // GL Client Normal Array is Disabled by default
     NormalManager::NormalManager()
	  :TwoSourceVectorManager(BIND_STATE)
     {
     }

     void NormalManager::normal3f(float nx,float ny,float nz)
     {
	  //TODO 
	  //if normal array is enabled ,what behavie is defined 
	  //when glNormal3f is called?
	  //currently only assert false;

	  assert(!vertexArrayEnabled());

	  setValue(Vector(nx,ny,nz));

     }

     void NormalManager::normalPointer(DataType type,
	       size_t stride, const void *pointer)
     {
	  vertexArrayChange(3,type,stride,pointer);
     }


} /* my_gl */
