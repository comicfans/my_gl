/*
 * =====================================================================================
 *
 *       Filename:  Image.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 12:18:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "Image.hpp"
#include <cassert>

namespace my_gl {

     RGBARef::RGBARef(uint8_t *bytes):
	       _bytes(bytes),
	       R(bytes[0]),
	       G(bytes[1]),
	       B(bytes[2]),
	       A(bytes[3])
	  {};

     Image::Image(int widthSet,int heightSet)
	       :width(widthSet),height(heightSet),_imageBytesPtr(new uint8_t[width*height*4]){}

     int Image::byteSize()const
     {
	  return width*height*4;
     }

     RGBARef Image::operator()(int yIdx,int xIdx)
	  {
	       assert(yIdx>=0 && yIdx <=height && xIdx>=0 && xIdx<width);

	       return RGBARef(_imageBytesPtr.get()+(width*yIdx+xIdx)*4);
	  }


     uint8_t *Image::rawData()
     {
	  return _imageBytesPtr.get();
     }
} /* my_gl */
