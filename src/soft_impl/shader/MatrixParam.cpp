/*
 * =====================================================================================
 *
 *       Filename:  Global.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-2 15:12:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "MatrixParam.hpp"

namespace my_gl {

 	  
     void MatrixParam::updateAll(const Matrix4& modelViewSet,
		    const Matrix4& projectionSet,
		    const Matrix4& textureSet)
     {

	  modelView=modelViewSet;

	  projection=projectionSet;

	  texture=textureSet;

	  //update others

	     modelViewInverse=
		  modelView.inverse();
	     modelViewInverseTranspose=
		  modelViewInverse.transpose();

	     projectionInverse=
		  projection.inverse();
	     projectionInverseTranspose=
		  projectionInverse.transpose();

	     modelViewProjection=
		  projection;
	     modelViewProjection*=modelView;
	     modelViewProjectionInverse=
		  modelViewProjection.inverse();
	     modelViewProjectionInverseTranspose=
		  modelViewProjectionInverse.transpose();

	     textureInverse=
		  texture.inverse();
	     textureInverseTranspose=
		  textureInverse.transpose();

	     //normal matrix is the inverse matrix of 
	     //upper left 3x3 of modelView 
	     Matrix3 upperLeft;
	     for(int i=0;i<3;++i)
	     {
		  for (int j=0; j<3; ++j)
		  {
		       upperLeft(i,j)=modelView(i,j);
		  }
	     }

	     normal=upperLeft.inverse().transpose();

     }
	
} /* my_gl */
