/*
 * =====================================================================================
 *
 *       Filename:  Vector.cpp
 *
 *    Description:  implementation of Vector
 *
 *        Version:  1.0
 *        Created:  2011-9-14 14:00:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Vector.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>

using std::fill_n;
using std::copy_n;
using std::sin;
using std::cos;
using std::sqrt;
using std::for_each;
using std::divides;
using std::bind;
using std::placeholders::_1;

namespace my_gl {

     Vector::Vector(bool fillZero)noexcept
     {
	  if (fillZero)
	  {
	       fill_n(_values,LENGTH,0);
	  }
	  //always make w component 1
	  _values[LENGTH-1]=1;
     }

     Vector::Vector(float fx,float fy,float fz,float fw)noexcept
     {
	  _values[0]=fx;
	  _values[1]=fy;
	  _values[2]=fz;
	  _values[3]=fw;
     }


     float& Vector::operator()(size_t idx)noexcept
     {
	  assert(idx<LENGTH);
	  return _values[idx];
     }

     float& Vector::operator[](size_t idx)noexcept
     {return operator()(idx);}

     const float& Vector::operator[](size_t idx)const noexcept
     {return operator[](idx);}

     const float& Vector::operator()(size_t idx) const noexcept
     {
	  return const_cast<Vector&>(*this)(idx);
     }

     Vector& Vector::operator=(const Vector& rhs)
     {
	  copy_n(rhs._values,LENGTH,_values);
	  return *this;
     }

     const float* Vector::values()const noexcept
     {return _values;}

     float * Vector::values()noexcept
     {return _values;}

     inline float sq(float value){return value*value;}

     void normalize(float * values)
     {
	  float lengthSq=sq(values[0])+sq(values[1])+sq(values[2]);

	  float length=sqrt(lengthSq);

	  for_each(values,values+3,bind(divides<float>(),_1,length));
     }


} /* my_gl */
