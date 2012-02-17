/*
 * =====================================================================================
 *
 *       Filename:  MatrixStack.cpp
 *
 *    Description:  implementation of MatrixStack
 *
 *        Version:  1.0
 *        Created:  2011-9-13 17:09:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "MatrixStack.hpp"

     
extern template class std::stack<my_gl::Matrix4>;

namespace my_gl {

     MatrixStack::MatrixStack()
     {
	  stack<Matrix4>::push(Matrix4::identity());
     }

     void MatrixStack::push()
     {
	  stack<Matrix4>::push(top());
     }

     void MatrixStack::multiTop(const Matrix4 &rhs)
     {
	  top()*=rhs;
     }
	
} /* my_gl */
