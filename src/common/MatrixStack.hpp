/*
 * =====================================================================================
 *
 *       Filename:  MatrixStack.hpp
 *
 *    Description:  a stack of Matrix
 *
 *        Version:  1.0
 *        Created:  2011-9-13 17:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MATRIX_STACK_HPP

#define MATRIX_STACK_HPP

#include <stack>

#include "Matrix.hpp"

namespace my_gl {

     using std::stack;

     class MatrixStack:protected stack<Matrix4> {
     public:

	  MatrixStack();

	  void multiTop(const Matrix4& rhs);

	  void push();

	  using stack<Matrix4>::pop;

	  using stack<Matrix4>::top;
     
     };

	
} /* my */

extern template class std::stack<my_gl::Matrix4>;

#endif /* end of include guard: MATRIX_STACK_HPP */
