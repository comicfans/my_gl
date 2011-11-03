/*
 * =====================================================================================
 *
 *       Filename:  Global.hpp
 *
 *    Description:  a struct contains all matrix 
 *
 *        Version:  1.0
 *        Created:  2011-9-29 19:43:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MATRIX_PARAM_HPP

#define MATRIX_PARAM_HPP

#include "common/Matrix.hpp"

namespace my_gl {

     struct MatrixParam{

	  Matrix4 modelView;
	  Matrix4 projection;
	  Matrix4 modelViewProjection;
	  Matrix4 texture;
	  Matrix4 normal;

	  Matrix4 modelViewInverse;
	  Matrix4 projectionInverse;
	  Matrix4 modelViewProjectionInverse;
	  Matrix4 textureInverse;

	  Matrix4 modelViewTranspose;
	  Matrix4 projectionTranspose;
	  Matrix4 modelViewProjectionTranspose;
	  Matrix4 textureTranspose;

	  Matrix4 modelViewInverseTranspose;
	  Matrix4 projectionInverseTranspose;
	  Matrix4 modelViewProjectionInverseTranspose;
	  Matrix4 textureInverseTranspose;

	  void updateAll(const Matrix4& modelViewSet,
		    const Matrix4& projectionSet,
		    const Matrix4& textureSet);
 
     } /* optional variable list */;
	
} /* my_gl */

#endif /* end of include guard: MATRIX_PARAM_HPP */
