/*
 * =====================================================================================
 *
 *       Filename:  Rectangle.hpp
 *
 *    Description:  store x,y,width,height parameter
 *    used as ViewportParameter and scissor parameter
 *
 *        Version:  1.0
 *        Created:  2011-11-18 13:49:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef RECTANGLE_HPP

#define RECTANGLE_HPP

#include <cstdint>

namespace my_gl {

     struct Rectangle{
	  int32_t x;
	  int32_t y;
	  uint32_t width;
	  uint32_t height;
     } /* optional variable list */;

     typedef Rectangle ViewportParameter;
     typedef Rectangle ScissorParameter;
	
} /* my_gl */




#endif /* end of include guard: RECTANGLE_HPP */
