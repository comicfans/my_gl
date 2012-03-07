/*
 * =====================================================================================
 *
 *       Filename:  TextureFunc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-9 11:15:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TextureFunc.hpp"

namespace my_gl {
	

     /** 
      * @brief use texture RGB components and fragment alpha
      * 
      * @param fragmentColor
      * @param textureColor
      * 
      * @return 
      */
     static Vec4 RGBReplace
	  (const Vec4& fragmentColor,const Vec4& textureColor)
	  {

	       Vec4 ret(textureColor);

	       ret[3]=fragmentColor[3];

	       return ret;
	  }

     static Vec4 RGBModulate
	  (const Vec4& fragmentColor,const Vec4& textureColor)
	  {
	       Vec4 ret=componentMul(fragmentColor,textureColor);

	       ret[3]=fragmentColor[3];

	       return ret;
	  }

     static Vec4 RGBDecal
	  (const Vec4& fragmentColor,const Vec4& textureColor)
	  {
	       //same as RGBReplace
	       return RGBReplace(fragmentColor,textureColor);
	  }

     static Vec4 RGBAReplace
	  (const Vec4& fragmentColor,const Vec4& textureColor)
	  {
	       return textureColor;
	  }

     static Vec4 RGBAModulate
	  (const Vec4& fragmentColor,const Vec4& textureColor)
	  {
	       return componentMul(fragmentColor,textureColor);
	  }
     static Vec4 RGBADecal
	  (const Vec4& fragmentColor,const Vec4& textureColor)
	  {
	       float As=textureColor[3];
	       Vec4 ret=fragmentColor*(1-As)+textureColor*As;
	       ret[3]=fragmentColor[3];
	       return ret;
	  }

     static TextureFunc::Func ALL_FUNC[2][3]={
	  {RGBReplace,RGBModulate,RGBDecal},
	  {RGBAReplace,RGBAModulate,RGBADecal}
     };

     TextureFunc::TextureFunc 
	  (GLenum texEnvMode)
	  :_texEnvMode(texEnvMode)
	  {
	  }

     Vec4 TextureFunc::operator()
	  (GLenum textureFormat,
	   const Vec4& fragmentColor,const Vec4& textureColor)const
	  {
	       int textureFormatIndex=textureFormat==GL_RGB?0:1;
	       int texEnvModeIndex=_texEnvMode==GL_REPLACE?0:(_texEnvMode==GL_MODULATE?1:2);

	       return ALL_FUNC[textureFormatIndex][texEnvModeIndex]
		    (fragmentColor,textureColor);
	  }
} /* my_gl */
