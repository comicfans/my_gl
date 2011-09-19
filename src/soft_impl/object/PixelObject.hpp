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

     using boost::noncopyable;

     class PixelObject :public BufferObject{
     public:
	PixelObject (Name name);

	void bindImage(size_t width,size_t height,
		  ImageFormat format,StoreType type,void *p);

	ImageFormat getFormat()const noexcept;

	StoreType getType()const noexcept;

	void subImage(int xOffset,int yOffset,
		  size_t width,size_t height,
		  ImageFormat format,StoreType type,void *p)noexcept;

     private:
	size_t _width;
	size_t _height;
	ImageFormat _format;
	StoreType _type;
     };
	
} /* my_gl */

#endif /* end of include guard: PIXEL_OBJECT_HPP */
