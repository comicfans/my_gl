/*
 * =====================================================================================
 *
 *       Filename:  ColorBuffer.hpp
 *
 *    Description:  OpenGL color buffer 
 *    which final pixel is reached, store RGBA pixel in float format
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
#include "common/Vec.hpp"

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

	  /** 
	   * @brief glClearColor ,rgba value is used to 
	   * clear whole buffer
	   * 
	   * @param r
	   * @param g
	   * @param b
	   * @param a
	   */
	  void clearColor(float r,float g,float b,float a);

	  virtual void clear();

	  virtual ~ColorBuffer();

	  /** 
	   * @brief which index of frameBuffer vector
	   * need refactor ?
	   */
	  static const int ORDER_INDEX=0;

     private:

	  multi_array<Vec4,2> _impl;

	  Vec4 _clearColor;

     };
	
} /* my_gl */


#endif /* end of include guard: COLOR_BUFFER_HPP */
