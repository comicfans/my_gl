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


     TextureObject::TextureObject (size_t width,size_t height,
		  ImageFormat format,StoreType type,void *p)
	  :_width(width),_height(height),_format(format),_type(type),
	  _pointer(p,width*height*TYPE_SIZE[int(type)]);
     {
     }
	
} /* my_gl */
