/*
 * =====================================================================================
 *
 *       Filename:  TestFunction.hpp
 *
 *    Description:  function to test (float equal)
 *
 *        Version:  1.0
 *        Created:  2011-10-26 11:18:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_FUNCTION_HPP

#define TEST_FUNCTION_HPP

#include "common/VecFwd.hpp"
#include "common/Matrix.hpp"

namespace my_gl {

     bool equal(float lhs,float rhs,unsigned errorFactor=1000);

     void assertEqual(float lhs,float rhs,unsigned errorFactor=1000);

     bool equal (const Vec4& lhs,const Vec4& rhs);

     bool assertEqual(const Vec4& lhs,const Vec4& rhs);
	  
     bool assertEqual(const Matrix4& lhs,const Matrix4& rhs,unsigned errorFactor=100);

	
     Matrix4 randMatrix();

     Vec4 randVec();
     int myRand();
} /* my_gl */

#endif /* end of include guard: TEST_FUNCTION_HPP */
