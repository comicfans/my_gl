/*
 * =====================================================================================
 *
 *       Filename:  ColorBuffer.cpp
 *
 *    Description:  OpenGL color buffer ,
 *    store RGBA data in float format 
 *    
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
	  _impl(extents[height][width])
     {}

	  Vec4& ColorBuffer::operator()
	       (const WinCoord& winCoord)
	  {
	       return _impl[winCoord.y()][winCoord.x()];
	  }

	  Vec4& ColorBuffer::operator()(size_t x,size_t y)
	  {
	       return _impl[y][x];
	  }

	  const Vec4& ColorBuffer::operator()(size_t x,size_t y)const
	  {
	       return _impl[y][x];
	  }
	  const Vec4& ColorBuffer::operator()
	       (const WinCoord& winCoord)const
	  {
	       return _impl[winCoord.y()][winCoord.x()];
	  }

	  size_t ColorBuffer::width()const
	  {return _impl.shape()[1];}

	  size_t ColorBuffer::height()const
	  {
	       return _impl.shape()[0];
	  }

	  void ColorBuffer::clearColor(float r,float g,float b,float a)
	  {
	       _clearColor={r,g,b,a};
	  }

	  ColorBuffer::~ColorBuffer(){}

	  void ColorBuffer::clear()
	  {
	       fill_n(_impl.origin(),_impl.num_elements(),_clearColor);
	  }
} /* my_gl */
