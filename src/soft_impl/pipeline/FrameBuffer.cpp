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

     FrameBuffer::FrameBuffer (size_t heigt,size_t width):
	  SuperType(extents[heigt][width])
     {}

	  Vec4& FrameBuffer::operator()
	       (const WindowCoordinates& winCoord)
	  {
	       return (*this)[winCoord.first][winCoord.second];
	  }

	  const Vec4& FrameBuffer::operator()
	       (const WindowCoordinates& winCoord)const
	  {
	       return (*this)[winCoord.first][winCoord.second];
	  }

} /* my_gl */
