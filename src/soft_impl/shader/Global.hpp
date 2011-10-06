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

#ifndef GLOBAL_HPP

#define GLOBAL_HPP

#include "common/Matrix.hpp"

namespace my_gl {

     struct Global {

	  Matrix modelView;
	  Matrix projection;
	  Matrix modelViewProjection;
	  Matrix texture;
	  Matrix normal;

	  Matrix modelViewInverse;
	  Matrix projectionInverse;
	  Matrix modelViewProjectionInverse;
	  Matrix textureInverse;

	  Matrix modelViewTranspose;
	  Matrix projectionTranspose;
	  Matrix modelViewProjectionTranspose;
	  Matrix textureTranspose;

	  Matrix modelViewInverseTranspose;
	  Matrix projectionInverseTranspose;
	  Matrix modelViewProjectionInverseTranspose;
	  Matrix textureInverseTranspose;
     } /* optional variable list */;
	
} /* my_gl */

#endif /* end of include guard: GLOBAL_HPP */
