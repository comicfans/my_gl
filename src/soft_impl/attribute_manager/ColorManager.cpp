/*
 * =====================================================================================
 *
 *       Filename:  ColorManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-21 10:19:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ColorManager.hpp"
#include "common/UniqueVec4Provider.hpp"

namespace my_gl {

     ColorManager::ColorManager()
	  :TwoSourceVec4Manager(BIND_STATE)
     {
	  //default current color is 1,1,1,1
	  //see glColor4f
	  setValue(Vec4(1,1,1,1));
     }

     void ColorManager::color4f(float red,float green,
	       float blue,float alpha)
     {
	  setValue(Vec4(red,green,blue,alpha));
     }


     void ColorManager::color4ub(uint8_t red,uint8_t green,
	       uint8_t blue,uint8_t alpha)
     {
	  const float fullRange=255;
	  color4f(red/fullRange,red/fullRange,
		    green/fullRange,alpha/fullRange);
     }

     void ColorManager::colorPointer(int componentSize,
	       GLenum type,size_t stride,const void *pointer)
     {
	  vertexArrayChange(componentSize, type, 
		    stride, pointer,true);
     }
	
} /* my_gl */
