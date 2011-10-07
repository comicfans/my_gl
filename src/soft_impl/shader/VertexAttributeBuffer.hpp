/*
 * =====================================================================================
 *
 *       Filename:  VertexAttributeBuffer.hpp
 *
 *    Description:  a buffer to store vertex shader processed
 *    vertex attribute
 *    
 *
 *        Version:  1.0
 *        Created:  2011-10-6 13:33:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef VERTEX_ATTRIBUTE_BUFFER_HPP

#define VERTEX_ATTRIBUTE_BUFFER_HPP

#include <boost/multi_array.hpp>


#include "common/Vec4.hpp"

namespace my_gl {

     //TODO var width
     using boost::multi_array;
     class VertexAttributeBuffer :public multi_array<Vec4,2>
     {
     public:

	  size_t length()const ;

	  void resize(size_t length);

	  Vec4* data(size_t index);
     };
	
} /* my_gl */

#endif /* end of include guard: VERTEX_ATTRIBUTE_BUFFER_HPP */

