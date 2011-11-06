/*
 * =====================================================================================
 *
 *       Filename:  TextureObject.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-4 15:22:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEXTURE_OBJECT_HPP

#define TEXTURE_OBJECT_HPP

#include <functional>

#include "PixelObject.hpp"


namespace my_gl {

     using std::function;

     struct TexelPos;

     class TextureObject : PixelObject{
     public:

     	TextureObject (Name name);

	Vec4 operator(float s,float t)const;

	Vec4 operator(const TexelPos& texelPos)const;

	typedef function<float(float)> Warpper;

	void texParameter
	     (TexWarpName warpName,TexWarpMode warpMode);

	void texParameter
	     (TexFilterName filterName,TexFilterMode filterMode);

     private:

	TexWarpMode _stWarp[2];

	Warpper _stWarpper[2];

     };
	
} /* my_gl */


#endif /* end of include guard: TEXTURE_OBJECT_HPP */
