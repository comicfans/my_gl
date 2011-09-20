/*
 * =====================================================================================
 *
 *       Filename:  TwoSourceVectorManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-21 1:50:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TwoSourceVectorManager.hpp"

#include <cassert>

#include "common/UniqueVectorProvider.hpp"

namespace my_gl {

     TwoSourceVectorManager::TwoSourceVectorManager(BindState bindState)
	  :VectorManager(bindState){}

     void TwoSourceVectorManager::clientStateChangeCallback(bool vertexArrayEnabled)
     {

	  if (vertexArrayEnabled)
	  {
	       _uniqueValue=static_cast<UniqueVectorProvider&>(getProvider()).value();
	  }
	  else
	  {
	       _pImpl.reset(new UniqueVectorProvider(_uniqueValue));
	  }

     }

     void TwoSourceVectorManager::setValue(const my_gl::Vector &value)
     {
	  assert(!vertexArrayEnabled());
	       
	  static_cast<UniqueVectorProvider&>(getProvider()).setValue(value);
	 _uniqueValue=value;
     }
	
} /* my_gl */
