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

#include <algorithm>

#include "common/PixelUnpacker.hpp"
#include "common/UntypedArray.hpp"

namespace my_gl {

     using std::copy_n;

     PixelObject::PixelObject (Name name)
	  :BufferObject(name)
     {
     }

	
     GLenum PixelObject::getFormat()const 
     {return _format;}

	GLenum PixelObject::getType()const 
	{
	     return _type;
	}


     void PixelObject::bindImage(size_t width,size_t height,
		  GLenum format,GLenum type,const void *p)
     {
	  _width=width;
	  _height=height;
	  _type=type;
	  _format=format;
	  _dataPointer.reset(new UntypedArray(
			 width*height*4*sizeof(float),nullptr));

	  PixelUnpacker unpacker(p,_dataPointer->get<float>(),width,height,
		    format,type);

	  unpacker.unpack();
     }

     void PixelObject::directBindImage
	  (size_t width,size_t height,GLenum internalFormat)
	  {
	       size_t byteSize=width*height*4*sizeof(float);

	       _dataPointer.reset(new UntypedArray(byteSize,nullptr));

	       _width=width;
	       _height=height;

	       _format=internalFormat;

	       //this is only a stub
	       _type=GL_UNSIGNED_BYTE;

	  }

	
     void PixelObject::directSubImage(int xOffset,int yOffset,
		  size_t width,const float *p)
     {
	  size_t floatOffset=(yOffset*_height+xOffset)*4;

	  size_t copyNumber=width*4;

	  copy_n(p,copyNumber,_dataPointer->
		    get<float>()+floatOffset);
     }

     size_t PixelObject::width()const
     {
	  return _width;
     }

     size_t PixelObject::height()const
     {
	  return _height;
     }

     void PixelObject::subImage(int xOffset,  int yOffset,
	        size_t width,  size_t height,  GLenum format,
		GLenum type,const void *p)
     {
	  assert(xOffset>=0 && xOffset<_width);
	  assert(yOffset>=0 && yOffset<_height);

	  PixelUnpacker unpacker(p,_dataPointer->get<float>(),width,height,
		    format,type,_width*height+width);

	  unpacker.unpack();
     }
	
} /* my_gl */
