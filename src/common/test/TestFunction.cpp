/*
 * =====================================================================================
 *
 *       Filename:  TestFunction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-26 11:19:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TestFunction.hpp"

#include <cmath>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "common/Vec.hpp"
#include "common/Matrix.hpp"

namespace my_gl {

     using std::abs;
     using std::rand;
     using std::cout;
     using std::endl;
     using std::max;

     bool equal(float lhs,float rhs,unsigned errorFactor)
     {

	  float delta=abs(lhs-rhs);

	  if (lhs==0 || rhs==0)
	  {
	       return delta<1.0/errorFactor;
	  }

	  float threshold=max(abs(lhs),abs(rhs))/errorFactor;

	  return delta<=threshold;
     }

     void assertEqual(float lhs,float rhs,unsigned errorFactor)
     {
	  if (!equal(lhs,rhs,errorFactor))
	  {
	       cout<<"lhs is "<<lhs<<" but rhs is "<<rhs<<endl;
	       assert(false);
	  }
     }

     bool equal (const Vec4& lhs,const Vec4& rhs)
     {
	  bool prevEqual=true;
	  for (size_t i=0; i<Vec4::LENGTH; ++i)
	  {
	       prevEqual=equal(lhs[i],rhs[i]);
	       if (!prevEqual)
	       {
		    return false;
	       }
	  }
	  return true;
     }

     template <typename M>
	  bool assertEqual(const M& lhs,const M& rhs,unsigned errorFactor)
	  {
	       auto values1=lhs.values(),
		    values2=rhs.values();
	       for (int i=0; i<M::ELEMENTS_NUMBER; ++i)
	       {
		    assertEqual(values1[i],values2[i],errorFactor);
	       }
	       return true;

	  }

     template bool assertEqual<Matrix4>(const Matrix4&,const Matrix4&,unsigned);
     template bool assertEqual<Matrix3>(const Matrix3&,const Matrix3&,unsigned);

     int myRand()
     {
	  int ret=rand();

	  ret-=RAND_MAX/2;

	  return ret;
     }
     Vec4 randVec()
     {
	  Vec4 ret;

	  for (int i=0; i<Vec4::LENGTH; ++i)
	  {
	       ret[i]=myRand();
	  }

	  return ret;
     }

     bool assertEqual(const Vec4& lhs,const Vec4& rhs)
     {
	  assert(equal(lhs,rhs));
	  return true;

     }

     template<typename M>
     M randMatrix()
     {

	  M matrix;

	  for(int i=0;i<M::LENGTH;++i)
	  {
	       for (int j=0; j<M::LENGTH; ++j)
	       {
		    matrix(i,j)=float(myRand())/INT_MAX;
	       }
	  }

	  return matrix;

     }

     template Matrix3 randMatrix<Matrix3>();
     template Matrix4 randMatrix<Matrix4>();


} /* my_gl */
