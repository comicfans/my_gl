/*
 * =====================================================================================
 *
 *       Filename:  ColorBuffer.hpp
 *
 *    Description:  which final pixel is reached
 *
 *        Version:  1.0
 *        Created:  2011-10-22 16:08:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COLOR_BUFFER_HPP

#define COLOR_BUFFER_HPP

#include <boost/multi_array.hpp>

#include "FrameBuffer.hpp"
#include "common/Vec4.hpp"

namespace my_gl {


     using boost::multi_array;

     class WinCoord;

     class ColorBuffer :public FrameBuffer{
     public:

	  ColorBuffer (size_t width,size_t height);

	  Vec4& operator()(const WinCoord& winCoord);

	  Vec4& operator()(size_t y,size_t x);

	  const Vec4& operator()(const WinCoord& winCoord)const;

	  size_t width()const;

	  size_t height()const;

	  void clearColor(float r,float g,float b,float a);

	  virtual void clear();

	  virtual ~ColorBuffer();

     private:

	  multi_array<Vec4,2> _impl;

	  Vec4 _clearColor;

     };
	
} /* my_gl */


#endif /* end of include guard: COLOR_BUFFER_HPP */
