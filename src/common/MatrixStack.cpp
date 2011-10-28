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

     
template class std::stack<my_gl::Matrix>;

namespace my_gl {

     MatrixStack::MatrixStack()
     {
	  stack<Matrix>::push(Matrix::identity());
     }

     void MatrixStack::push()
     {
	  stack<Matrix>::push(top());
     }

     void MatrixStack::multiTop(const my_gl::Matrix &rhs)
     {
	  top()*=rhs;
     }
	
} /* my_gl */
