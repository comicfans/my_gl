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

     void MatrixStack::push()
     {
	  stack<Matrix>::push(top());
     }
	
} /* my_gl */
