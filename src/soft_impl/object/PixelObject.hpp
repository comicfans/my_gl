/*
 * =====================================================================================
 *
 *       Filename:  PixelObject.hpp
 *
 *    Description:  PixelObject respect to glTexImage2D/glTexSubImage2D
 *
 *        Version:  1.0
 *        Created:  2011-9-13 21:06:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PIXEL_OBJECT_HPP

#define PIXEL_OBJECT_HPP

#include <cstddef>


#include "BufferObject.hpp"
#include "Enum.hpp"

namespace my_gl {


     class PixelObject :public BufferObject{
     public:
	PixelObject (Name name);

	void bindImage(size_t width,size_t height,
		  ImageFormat format,StoreType type,const void *p);

	/** 
	 * @brief for copyTexImage2D use only,
	 * because pixels in frameBuffer is not always continus
	 * (x!=0),so call directBindImage only extends underline
	 * UntypedArray to right size, than use directSubImage to 
	 * fill every line of image
	 * 
	 * @param width
	 * @param height
	 * 
	 * @return 
	 */
	void directBindImage
	     (size_t width,size_t height);

	ImageFormat getFormat()const ;

	StoreType getType()const ;

	size_t width()const;

	size_t height()const;

	void subImage(int xOffset,int yOffset,
		  size_t width,size_t height,
		  ImageFormat format,StoreType type,const void *p);

	void directSubImage(int xOffset,int yOffset,
		  size_t width,const float *p);

     private:
	size_t _width;
	size_t _height;
	ImageFormat _format;
	StoreType _type;
     };
	
} /* my_gl */

#endif /* end of include guard: PIXEL_OBJECT_HPP */
