/*
 * =====================================================================================
 *
 *       Filename:  DepthBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 10:23:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "DepthBuffer.hpp"

#include <algorithm>

#include "pipeline/rasterizer/WinCoord.hpp"

namespace my_gl {

     using std::fill_n;

     using boost::extents;

     DepthBuffer::DepthBuffer(size_t width,size_t height)
	  :_impl(extents[height][width])
     {
	  //glspec default GL_DEPTH_CLEAR_VALUE
	  _clearDepth=1;
     }

     DepthBuffer::~DepthBuffer()
     {}

     void DepthBuffer::clearDepth(float depth)
     {
	  _clearDepth=depth;
     }

     size_t DepthBuffer::width()const
     {
	  return _impl.shape()[1];
     }
	  size_t DepthBuffer::height()const
	  {
	       return _impl.shape()[0];

	  }



	  float DepthBuffer::operator()(const WinCoord& winCoord)const
	  {
	       return _impl[winCoord.y()][winCoord.x()];
	  }

	  float& DepthBuffer::operator()(const WinCoord& winCoord)
	  {
	       return _impl[winCoord.y()][winCoord.x()];
	  }

     void DepthBuffer::clear()
     {
	  fill_n(_impl.origin(),_impl.num_elements(),_clearDepth);
	  
     }
	
} /* my_gl */
