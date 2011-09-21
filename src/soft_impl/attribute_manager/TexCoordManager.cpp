/*
 * =====================================================================================
 *
 *       Filename:  TexCoordManager.cpp
 *
 *    Description:  implementation of TexCoordManager
 *
 *        Version:  1.0
 *        Created:  2011-9-21 11:45:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TexCoordManager.hpp"
#include "common/UniqueVectorProvider.hpp"

namespace my_gl {

     TexCoordManager::TexCoordManager()
	  :VectorManager(BIND_STATE)
     {}

     void TexCoordManager::texCoordPointer(int componentSize,
	       DataType type,size_t stride,const void *pointer)
     {
	  vertexArrayChange(componentSize, type, stride, pointer);
     }

	
} /* my_gl */
