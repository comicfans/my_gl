/*
 * =====================================================================================
 *
 *       Filename:  TwoSourceVec4Manager.cpp
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

#include "TwoSourceVec4Manager.hpp"

#include <cassert>

#include "common/UniqueVec4Provider.hpp"

namespace my_gl {

     TwoSourceVec4Manager::TwoSourceVec4Manager(GLenum bindState)
	  :Vec4Manager(bindState)
     {
	  clientStateChangeCallback(false);
     }

     void TwoSourceVec4Manager::clientStateChangeCallback(bool vertexArrayEnabled)
     {

	  if (vertexArrayEnabled)
	  {
	       _uniqueValue=static_cast
		    <UniqueVec4Provider&>(*_pImpl).getValue(0);
	  }
	  else
	  {
	       _pImpl.reset(new UniqueVec4Provider(_uniqueValue));
	  }

     }

     void TwoSourceVec4Manager::setValue(const my_gl::Vec4 &value)
     {
	  assert(!vertexArrayEnabled());
	       
	  static_cast<UniqueVec4Provider&>
	       (*_pImpl).setValue(value);
	 _uniqueValue=value;
     }
	
} /* my_gl */
