/*
 * =====================================================================================
 *
 *       Filename:  TextureObject.cpp
 *
 *    Description:  implementation of TextureObject
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

#include "TextureObject.hpp"


namespace my_gl {

     const int TYPE_SIZE[4]={1,2,2,2};

     static int byteSize(size_t width,size_t height,StoreType type)
     {
	  return width*height*TYPE_SIZE[int(type)];
     }

     TextureObject::TextureObject (Name name)
	  :BufferObject(name)
     {
     }

     

     void TextureObject::bindImage(size_t width,size_t height,
		  ImageFormat format,StoreType type,void *p)
     {
	  _width=width;
	  _height=height;
	  _type=type;
	  _format=format;
	  bindData(byteSize(width,height,type),p);
     }

     void TextureObject::subImage(int xOffset,  int yOffset,
	        size_t width,  size_t height,  void *p)noexcept
     {
	  assert(xOffset>=0 && xOffset<_width);
	  assert(yOffset>=0 && yOffset<_height);

	  int offset=byteSize(_width,yOffset,_type)+xOffset;
	  subData(offset, byteSize(width,height,_type),p);
     }
	
} /* my_gl */
