/*
 * =====================================================================================
 *
 *       Filename:  VertexAttributeBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-6 13:36:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "VertexAttributeBuffer.hpp"

#include "VertexShader.hpp"

namespace my_gl {

     using boost::extents;

     size_t VertexAttributeBuffer::length()const
     {
	  return shape()[0];
     }

     void VertexAttributeBuffer::resize(size_t length)
     {
	  multi_array<Vec4,2>::resize(extents
		    [length][VertexShader::OUT_SIZE]);
     }

     Vec4* VertexAttributeBuffer::data(size_t index)
     {
	  return origin()+index*VertexShader::OUT_SIZE;
     }
	
     const Vec4* VertexAttributeBuffer::data(size_t index)const
     {
	  return origin()+index*VertexShader::OUT_SIZE;
     }
	
} /* my_gl */
