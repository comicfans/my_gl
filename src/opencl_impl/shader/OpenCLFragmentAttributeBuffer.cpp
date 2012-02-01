/*
 * =====================================================================================
 *
 *       Filename:  OpenCLFragmentAttributeBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-28 20:25:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLFragmentAttributeBuffer.hpp"

namespace my_gl {

     OpenCLFragmentAttributeBuffer::OpenCLFragmentAttributeBuffer 
	  (size_t width,size_t height,size_t attributeNumber)
	  :FragmentAttributeBuffer(width,height,attributeNumber){}

     const void * OpenCLFragmentAttributeBuffer::getRawData()const
     {
	  return &(*this)(0,0)[0];
     }


} /* my_gl */
