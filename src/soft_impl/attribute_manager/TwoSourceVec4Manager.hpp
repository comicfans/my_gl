/*
 * =====================================================================================
 *
 *       Filename:  TwoSourceVec4Manager.hpp
 *
 *    Description:  can use vetex array/buffer object or single UniqueVec4Provider 
 *
 *        Version:  1.0
 *        Created:  2011-9-21 1:36:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TWO_SOURCE_VEC4_MANAGER_HPP

#define TWO_SOURCE_VEC4_MANAGER_HPP

#include "common/Vec4Manager.hpp"
#include "common/Vec.hpp"

namespace my_gl {

     class TwoSourceVec4Manager :public Vec4Manager{
     
	  public:

	       TwoSourceVec4Manager(GLenum bindState);

	  protected:

	       virtual void clientStateChangeCallback(bool vertexArrayEnabled);

	       void setValue(const Vec4& value);

	  private:

	       Vec4 _uniqueValue;
     
     };
	
} /* my_gl */



#endif /* end of include guard: TWO_SOURCE_VEC4_MANAGER_HPP */
