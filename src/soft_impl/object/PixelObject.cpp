/*
 * =====================================================================================
 *
 *       Filename:  PixelObject.cpp
 *
 *    Description:  implementation of PixelObject
 *
 *        Version:  1.0
 *        Created:  2011-9-13 21:19:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "PixelObject.hpp"
#include "common/PixelUnpacker.hpp"
#include "common/UntypedArray.hpp"

namespace my_gl {

     PixelObject::PixelObject (Name name)
	  :BufferObject(name)
     {
     }


     void PixelObject::bindImage(size_t width,size_t height,
		  ImageFormat format,StoreType type,void *p)
     {
	  _width=width;
	  _height=height;
	  _type=type;
	  _format=format;
	  _dataPointer.reset(new UntypedArray(
			 PixelUnpacker::calcTotalExpandedSize
			 (width, height, format, type),nullptr));

	  PixelUnpacker unpacker(p,_dataPointer->get<float>(),width,height,
		    format,type);

	  unpacker.unpack();
     }

     void PixelObject::subImage(int xOffset,  int yOffset,
	        size_t width,  size_t height,  ImageFormat format,
		StoreType type,void *p)
     {
	  assert(xOffset>=0 && xOffset<_width);
	  assert(yOffset>=0 && yOffset<_height);

	  PixelUnpacker unpacker(p,_dataPointer->get<float>(),width,height,
		    format,type,_width*height+width);

	  unpacker.unpack();
     }
	
} /* my_gl */
