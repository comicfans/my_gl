/*
 * =====================================================================================
 *
 *       Filename:  TexCoordManager.hpp
 *
 *    Description:  OpenGL Programming Guide said that
 *    		    when texCoord is integer , it will not be
 *    		    normalized ,but in GLSL Texture Lookup Functions
 *    		    sampler only accept float value (after normalized)
 *    		    so make it normalized
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

#include "common/Vec4Manager.hpp"

namespace my_gl {
     class TexCoordManager :public Vec4Manager{
     public:
     	TexCoordManager ();

	void texCoordPointer(int componentSize,DataType type,
		 size_t stride,const void* pointer);

	static const BindState BIND_STATE=BindState::TEXCOORD;
     
     };
	
} /* my_gl */


#endif /* end of include guard: TEX_COORD_MANAGER_HPP */
