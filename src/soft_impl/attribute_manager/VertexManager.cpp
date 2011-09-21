/*
 * =====================================================================================
 *
 *       Filename:  VertexManager.cpp
 *
 *    Description:  impl
 *
 *        Version:  1.0
 *        Created:  2011-9-20 23:03:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "VertexManager.hpp"

#include "common/BufferObjectVectorProvider.hpp"

namespace my_gl {

     VertexManager::VertexManager()noexcept
	  :VectorManager(BIND_STATE)
	  {}

     void VertexManager::vertexPointer(int componentSize, 
	       DataType type,size_t stride,const void* pointer)
     {
	  vertexArrayChange(componentSize,type,stride,pointer);
     }

	
} /* my_gl */
