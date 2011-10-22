/*
 * =====================================================================================
 *
 *       Filename:  PixelDrawer.hpp
 *
 *    Description:  callback function of drawing final pixel
 *
 *        Version:  1.0
 *        Created:  2011-10-22 17:31:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PIXEL_DRAWER_HPP

#define PIXEL_DRAWER_HPP


namespace my_gl {

     class FrameBuffer;
     class PixelDrawer {
	  public:

	       void onInit(size_t height,size_t width);

	       void onDraw(const FrameBuffer& frameBuffer);
     };
	
} /* my_gl */

#endif /* end of include guard: PIXEL_DRAWER_HPP */
