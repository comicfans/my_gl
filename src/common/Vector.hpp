/*
 * =====================================================================================
 *
 *       Filename:  Vector.hpp
 *
 *    Description:  simple vector float 4 
 *
 *        Version:  1.0
 *        Created:  2011-9-13 16:05:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VECTOR_HPP


#define VECTOR_HPP

#include <cstddef>

namespace my_gl {
     class Vector{
    
	  public:

	       Vector(bool fillZero=true)noexcept;
	       float& x;
	       float& y;
	       float& z;
	       float& w;
	       static const int LENGTH=4;

	       float& operator()(size_t idx)noexcept;
	       const float& operator()(size_t idx)const noexcept;
	  private:
	       float _values[LENGTH];
     	/* data */
     };
	
} /* my_gl */


#endif /* end of include guard: VECTOR_HPP */
