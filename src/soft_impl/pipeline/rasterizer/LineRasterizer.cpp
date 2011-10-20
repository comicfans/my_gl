/*
 * =====================================================================================
 *
 *       Filename:  LineRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-20 21:19:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LineRasterizer.hpp"

namespace my_gl {
     void LineRasterizer::elementRasterize
	  (ConstAttributeGroupRef* attributeGroupRefs,
	   FragmentAttributeBuffer& fragmentAttributeBuffer)
	  {

	       auto 
		    attributeGroup1=attributeGroupRefs[0],
	       attributeGroup2=attributeGroupRefs[1];

	       auto 
		    &point1=getVertex(attributeGroup1),
	       &point2=getVertex(attributeGroup2);


	       rasterize
		    (attributeGroup1,
		     attributeGroup2,
		     viewportCorrect(point1/point1.w()),
		     viewportCorrect(point2/point2.w()),
		     fragmentAttributeBuffer);
	  }

} /* my_gl */
