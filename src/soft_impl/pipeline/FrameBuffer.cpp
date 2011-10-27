/*
 * =====================================================================================
 *
 *       Filename:  FrameBuffer.cpp
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

#include "FrameBuffer.hpp"
#include "rasterizer/WindowCoordinates.hpp"

namespace my_gl {


     using boost::extents;

     FrameBuffer::FrameBuffer (size_t width,size_t height):
	  SuperType(extents[height][width])
     {}

	  Vec4& FrameBuffer::operator()
	       (const WindowCoordinates& winCoord)
	  {
	       return (*this)(winCoord.first,winCoord.second);
	  }

	  Vec4& FrameBuffer::operator()(size_t y,size_t x)
	  {
	       return (*this)[y][x];
	  }

	  const Vec4& FrameBuffer::operator()
	       (const WindowCoordinates& winCoord)const
	  {
	       return (*this)[winCoord.first][winCoord.second];
	  }

	  size_t FrameBuffer::width()const
	  {return shape()[1];}

	  size_t FrameBuffer::height()const
	  {
	       return shape()[0];
	  }
} /* my_gl */
