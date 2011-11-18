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

#include <cstddef>


namespace my_gl {

     class ColorBuffer;
     class PixelDrawer {
	  public:

	       virtual ~PixelDrawer();

	       virtual void onInit
		    (size_t height,size_t width)=0;

	       /** 
		* @brief will be called when frameBuffer 
		* is drawn
		* 
		* @param frameBuffer
		* 
		* @return 
		*/
	       virtual void onDraw
		    (const ColorBuffer& frameBuffer)=0;

	       /** 
		* @brief will be called when all drawing 
		* command is flushed
		*/
	       virtual void onFlush()=0;
     };
	
} /* my_gl */

#endif /* end of include guard: PIXEL_DRAWER_HPP */
