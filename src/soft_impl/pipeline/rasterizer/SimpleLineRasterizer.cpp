/*
 * =====================================================================================
 *
 *       Filename:  SimpleLineRasterizer.cpp
 *
 *    Description:  implementation
 *
 *        Version:  1.0
 *        Created:  2011-10-20 22:14:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SimpleLineRasterizer.hpp"

#include "pipeline/interpolator/Interpolator.hpp"
#include "pipeline/interpolator/CoordInfo.hpp"

namespace my_gl {
	
     void SimpleLineRasterizer::rasterize
	     (ConstAttributeGroupRef& attributeGroup1,
	      ConstAttributeGroupRef& attributeGroup2,
	      const CoordInfo& coord1,
	      const CoordInfo& coord2,
	      int majorDelta,int majorIndex,
	      int anotherDelta,int anotherIndex,
	      FragmentAttributeBuffer& fragmentAttributeBuffer,
	      const Interpolator& interpolator)
	     {

		       
		  float step=1.0/majorDelta;

		  for (int counter=1;counter<majorDelta; ++counter)
		  {
		       WindowCoordinates thisCoord;
		       thisCoord[majorIndex]=
			    coord1.windowCoord[majorIndex]+counter;

		       //use simple px=(1-lambda)*p1+lambda*p2;
		       float lambda=step*counter;

		       float anotherValue=(1-lambda)*
			    coord1.windowCoord[anotherIndex]+
			    lambda*
			    coord2.windowCoord[anotherIndex];

		       thisCoord[anotherIndex]=roundNearest(anotherValue);

		       float percent=interpolator.getPercent(
				 coord1.homogenousCoord,coord2.homogenousCoord,
				 thisCoord,counter,
				 Interpolator::MajorDim(majorIndex));


		       groupAction(attributeGroup1,attributeGroup2,
				 thisCoord,percent,fragmentAttributeBuffer);

		  }

	     }


} /* my_gl */
