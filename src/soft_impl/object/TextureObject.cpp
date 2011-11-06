/*
 * =====================================================================================
 *
 *       Filename:  TextureObject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-4 18:18:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TextureObject.hpp"

#include <cmath>

namespace my_gl {

     using std::min;
     using std::max;
     using std::fmod;
     using std::abs;

     float clamp(float value)
     {
	  return value>0?
	       min(value,1.0f):
	       max(value,0.0);
     }

     float repeat(float value)
     {
	  return value>0?
	       fmod(value,1.0f):
	       1.0f-fmod(-value,1.0);
     }

     float mirrorRepeat(float value)
     {
	  float mirrorPart=fmod(abs(value),2.0f);

	  return mirrorPart<1?
	       mirrorPart:1.0f-mirrorPart;
     }

     const static Warpper WARPPERS={clamp,repeat,mirrorRepeat};

     TextureObject::TextureObject(Name name)
	  :PixelObject(name)
     {
	  texParameter(TexWarpMode::TEXTURE_WARP_S,
		    TexWarpMode::REPEAT);
	  texParameter(TexWarpMode::TEXTURE_WARP_T,
		    TexWarpMode::REPEAT);
     }
	
     void TextureObject::texParameter
	  (TexWarpName warpName,TexWarpMode warpMode)
     {
	  int idx=int(warpName);
	  _stWarp[idx]=warpMode;
	  _stWarpper[idx]=WARPPERS[idx];
     }

     Vec4 TextureObject::operator(float s,float t)const
	{

	}

	Vec4 TextureObject::operator(const TexelPos& texelPos)const
	{
	     return operator()(texelPos.s,texelPos.t);
	}



} /* my_gl */
