/*
 * =====================================================================================
 *
 *       Filename:  ColorManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-21 10:04:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COLOR_MANAGER_HPP

#define COLOR_MANAGER_HPP

#include <cstdint>

#include "TwoSourceVectorManager.hpp"

namespace my_gl {

     class ColorManager :public TwoSourceVectorManager{

	  public:

	       ColorManager();

	       void color4f(float red,float green,float blue,float alpha)noexcept;

	       void color4ub(uint8_t red,uint8_t green,uint8_t blue,uint8_t alpha)noexcept;

	       void colorPointer(int componentSize,DataType type,
			 size_t stride,const void* pointer);

	       static const BindState BIND_STATE=BindState::COLOR;

     };
	
} /* my_gl */


#endif /* end of include guard: COLOR_MANAGER_HPP */
