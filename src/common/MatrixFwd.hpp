/*
 * =====================================================================================
 *
 *       Filename:  MatrixFwd.hpp
 *
 *    Description:  forward declaration of Matrix
 *
 *        Version:  1.0
 *        Created:  2011-11-3 12:07:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MATRIX_FWD_HPP

#define MATRIX_FWD_HPP
#include <cstddef>

namespace my_gl {

     template <size_t L>
	  class MatrixBase;

     typedef MatrixBase<2> Matrix2;
     typedef MatrixBase<3> Matrix3;
     typedef MatrixBase<4> Matrix4;
	
} /* my_gl */


#endif /* end of include guard: MATRIX_FWD_HPP */
