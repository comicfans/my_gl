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
	  :VectorManager(BindState::NORMAL),_normalArrayEnabled(false)
     {
	  _pImpl.reset(new UniqueVectorProvider());
     }

     VectorProvider& NormalManager::getProvider()noexcept
     {
	  return *_pImpl;
     }

     void NormalManager::normal(float nx,float ny,float nz)
     {
	  //TODO 
	  //if normal array is enabled ,what behavie is defined 
	  //when glNormal3f is called?
	  //currently only assert false;

	  assert(!_normalArrayEnabled);

	  static_cast<UniqueVectorProvider*>(_pImpl.get())
	       ->setValue(Vector(nx,ny,nz));
     }
	
} /* my_gl */
