/*
 * =====================================================================================
 *
 *       Filename:  TexCoordManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-21 10:36:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEX_COORD_MANAGER_HPP

#define TEX_COORD_MANAGER_HPP

#include "common/VectorManager.hpp"

namespace my_gl {
     class TexCoordManager :public VectorManager{
     public:
     	TexCoordManager ();

	void texCoordPointer(int componentSize,DataType type,
		 size_t stride,const void* pointer);

	static const BindState BIND_STATE=BindState::TEXCOORD;
     
     };
	
} /* my_gl */


#endif /* end of include guard: TEX_COORD_MANAGER_HPP */
