/*
 * =====================================================================================
 *
 *       Filename:  OpenCLDepthBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-8 15:50:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLDepthBuffer.hpp"

namespace my_gl {
     OpenCLDepthBuffer::OpenCLDepthBuffer
	  (size_t width,size_t height)
	  :DepthBuffer(width,height){}

     OpenCLDepthBuffer::~OpenCLDepthBuffer(){}

     void * OpenCLDepthBuffer::getRawData()
     {
	  return &_impl[0][0];
     }
	
} /* my_gl */
