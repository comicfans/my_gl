/*
 * =====================================================================================
 *
 *       Filename:  Vec.cpp
 *
 *    Description:  implementation of Vec
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

#include "Vec.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
#include <boost/foreach.hpp>

using std::fill_n;
using std::copy_n;
using std::sin;
using std::cos;
using std::sqrt;
using std::mismatch;
using std::divides;
using std::plus;
using std::transform;
using std::bind;
using std::placeholders::_1;

namespace my_gl {

    
     template<size_t L>
     VecBase<L>::VecBase(bool fillZero)
     {
	  if (fillZero)
	  {
	       fill_n(_values,LENGTH,0);
	  }
	  //always make w component 1
	  _values[LENGTH-1]=1;
     }

	 template<size_t L>
	 VecBase<L>::VecBase(float x,float y,float z,float w)
	 {
		 //temp hack
		 if(L<1)
		 {return;}
		 _values[0]=x;
		 if(L<2)
		 {return;}
		 _values[1]=y;
		 if(L<3)
		 {return;}
		 _values[2]=z;
		 if(L<4)
		 {return;}
		 _values[3]=w;
	 }


     template<size_t L>
	  VecBase<L>::VecBase(const VecBase& rhs)
	  {
	       *this=rhs;
	  }

     template<size_t L>
     VecBase<L>::VecBase(const float* values,size_t copyN)
     {
	  copy_n(values,copyN,_values);
     }

     template<size_t L>
     float& VecBase<L>::operator()(size_t idx)
     {
	  assert(idx<LENGTH);
	  return _values[idx];
     }

     template<size_t L>
     float& VecBase<L>::operator[](size_t idx)
     {return _values[idx];}

     template<size_t L>
     const float& VecBase<L>::operator[](size_t idx)const 
     {return _values[idx];}

     template<size_t L>
     const float& VecBase<L>::operator()(size_t idx) const 
     {
	  return _values[idx];
     }

     template<size_t L>
     VecBase<L>& VecBase<L>::operator=(const VecBase<L>& rhs)
     {
	  copy_n(rhs._values,LENGTH,_values);
	  return *this;
     }

     template<size_t L>
     const float* VecBase<L>::values()const 
     {return _values;}

     template<size_t L>
     float * VecBase<L>::values()
     {return _values;}

     template<size_t L>
     const float& VecBase<L>::x()const
     {return _values[0];}

     template<size_t L>
     const float& VecBase<L>::y()const
     {return _values[1];}

     template<size_t L>
     const float& VecBase<L>::z()const
     {return _values[2];}

     inline float sq(float value){return value*value;}

     void normalize(Vec3& vec )
     {
	  float vecLength=length(vec);

	  auto values=vec.values();

	  transform(values,values+3,values,bind(divides<float>(),_1,vecLength));
     }

     float length(const Vec3& vec3)
     {
	  auto *values=vec3.values();

	  float lengthSq=sq(values[0])+sq(values[1])+sq(values[2]);

	  return sqrt(lengthSq);
     }

     template<size_t L>
     void VecBase<L>::operator*=(float scalar)
     {
	  BOOST_FOREACH(float& component,_values)
	  {
	       component*=scalar;
	  }
     }

     template<size_t L>
     VecBase<L> VecBase<L>::operator*(float scalar)const
     {
	  VecBase<L> ret(*this);
	  ret*=scalar;
	  return ret;
     }

     template<size_t L>
     VecBase<L> VecBase<L>::operator-()const
     {
	  VecBase<L> ret(*this);

	  BOOST_FOREACH(float& component,ret._values)
	  {
	       component=-component;
	  }
	  return ret;
     }


    

     template<size_t L>
     void VecBase<L>::operator/=(float scalar)
     {
	  (*this)*=1/scalar;
     }

     template<size_t L>
     void VecBase<L>::operator+=(const VecBase<L>& rhs)
     {
	  transform(_values,_values+LENGTH,
		    rhs._values,_values,
		    plus<float>());
     }


     template<size_t L>
	  const float& VecBase<L>::w()const
	  {return _values[LENGTH-1]; }



     template<size_t L>
     bool VecBase<L>::operator==(const VecBase<L>& rhs)const
     {
	  return mismatch(_values,_values+LENGTH,rhs._values).
	       first==_values+LENGTH;
     }

     Vec4 componentMul(const Vec4& lhs,const Vec4& rhs)
     {
	  Vec4 ret(lhs);
	  for (size_t i=0; i<Vec4::LENGTH; ++i)
	  {
	       ret[i]*=rhs[i];
	  }
	  return ret;
     }

     
     template<size_t L>
     VecBase<L> VecBase<L>::operator+(const VecBase<L>& rhs)const
     {
	  VecBase<L> ret(*this);
	  ret+=rhs;
	  return ret;
     }

     template<size_t L>
     VecBase<L> VecBase<L>::operator-(const VecBase<L>& rhs)const
     {
	  VecBase<L> ret(*this);
	  ret+=(-rhs);
	  return ret;
     }

     template<size_t L>
     VecBase<L> VecBase<L>::operator/(float scalar)const
     {
	  assert(scalar!=0);
	  VecBase<L> ret(*this);
	  ret/=scalar;
	  return ret;
     }

     float dotProduct(const Vec3& lhs,const Vec3& rhs)
     {
	  float ret=0;
	  for (size_t i=0; i<Vec3::LENGTH; ++i)
	  {
	       ret+=lhs[i]*rhs[i];
	  }
	  return ret;
     }



 template struct VecBase<3>;
 template struct VecBase<2>;
  template struct VecBase<4>;
	

     //--------------------template instantiation//
     
     

     void perspectiveDivision(Vec4& vec4)
     {
	  assert(!isInfinit(vec4));
	  vec4/=vec4.w();
     }

     bool isInfinit(const Vec4& vec4)
     {
	  return vec4.w()==0;
     }


     Vec3 crossProduct3(const Vec3& lhs,const Vec3& rhs)
     {
	  Vec3 ret;

	  assert(false ||"not impled");


	  return ret;
     }



    
 }   /* my_gl */
