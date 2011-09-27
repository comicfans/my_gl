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
#include <algorithm>

using std::fill_n;
using std::copy_n;

namespace my_gl {

     Vector::Vector(bool fillZero)noexcept
	  :x(_values[0]),y(_values[1]),
	  z(_values[2]),w(_values[3]),
	  r(_values[0]),g(_values[1]),
	  b(_values[2]),a(_values[3])
     {
	  if (fillZero)
	  {
	       fill_n(_values,LENGTH,0);
	  }
	  //always make w component 1
	  w=1;
     }

     Vector::Vector(float fx,float fy,float fz,float fw)noexcept
	  :x(_values[0]),y(_values[1]),
	  z(_values[2]),w(_values[3]),
	  r(_values[0]),g(_values[1]),
	  b(_values[2]),a(_values[3])
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
} /* my_gl */
