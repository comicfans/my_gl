/*
 * =====================================================================================
 *
 *       Filename:  Vec4.hpp
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

#ifndef VEC4_HPP


#define VEC4_HPP

#include <cstddef>

namespace my_gl {
     struct Vec4{
    
	  public:

	       Vec4(bool fillZero=true);

	       Vec4(float fx,float fy,float fz=0,float fw=1);

	       Vec4& operator=(const Vec4& rhs);

	       static const int LENGTH=4;

	       float& operator()(size_t idx);
	       const float& operator()(size_t idx)const ;

	       float& operator[](size_t idx);
	       const float& operator[](size_t idx)const ;

	       const float* values()const ;
	       float * values() ;
	  private:
	       float _values[LENGTH];
     	/* data */
     };

     void normalize(float * values);
	
} /* my_gl */


#endif /* end of include guard: VEC4_HPP */
