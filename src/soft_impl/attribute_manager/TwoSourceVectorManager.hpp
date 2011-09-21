/*
 * =====================================================================================
 *
 *       Filename:  TwoSourceVectorManager.hpp
 *
 *    Description:  can use vetex array/buffer object or single UniqueVectorProvider 
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

#ifndef TWO_SOURCE_VECTOR_MANAGER_HPP

#define TWO_SOURCE_VECTOR_MANAGER_HPP

#include "common/VectorManager.hpp"
#include "common/Vector.hpp"

namespace my_gl {

     class TwoSourceVectorManager :public VectorManager{
     
	  public:

	       TwoSourceVectorManager(BindState bindState);

	  protected:

	       virtual void clientStateChangeCallback(bool vertexArrayEnabled);

	       void setValue(const Vector& value);

	  private:

	       Vector _uniqueValue;
     
     };
	
} /* my_gl */



#endif /* end of include guard: TWO_SOURCE_VECTOR_MANAGER_HPP */
