/*
 * =====================================================================================
 *
 *       Filename:  ColorBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-22 17:00:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ColorBuffer.hpp"

#include <algorithm>
#include "rasterizer/WinCoord.hpp"

namespace my_gl {


     using boost::extents;
     using std::fill_n;

     ColorBuffer::ColorBuffer (size_t width,size_t height):
	  SuperType(extents[height][width])
     {}

	  Vec4& ColorBuffer::operator()
	       (const WinCoord& winCoord)
	  {
	       return (*this)[winCoord.y()][winCoord.x()];
	  }

	  Vec4& ColorBuffer::operator()(size_t x,size_t y)
	  {
	       return (*this)[y][x];
	  }

	  const Vec4& ColorBuffer::operator()
	       (const WinCoord& winCoord)const
	  {
	       return (*this)[winCoord.y()][winCoord.x()];
	  }

	  size_t ColorBuffer::width()const
	  {return shape()[1];}

	  size_t ColorBuffer::height()const
	  {
	       return shape()[0];
	  }

	  void ColorBuffer::clearColor(float r,float g,float b,float a)
	  {
	       _clearColor=Vec4(r,g,b,a);
	  }

	  ColorBuffer::~ColorBuffer(){}

	  void ColorBuffer::clear()
	  {
	       fill_n(origin(),width()*height(),_clearColor);
	  }
} /* my_gl */
