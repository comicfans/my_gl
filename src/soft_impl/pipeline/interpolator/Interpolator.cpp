/*
 * =====================================================================================
 *
 *       Filename:  Interpolator.cpp
 *
 *    Description:  implementation of Interpolator
 *
 *        Version:  1.0
 *        Created:  2011-10-9 17:12:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Interpolator.hpp"

#include "pipeline/rasterizer/WindowCoordinates.hpp"


namespace my_gl {
	
     Interpolator::~Interpolator(){}
	  
     void Interpolator::calculate(const Vec4& source,
	       const Vec4& destination,float persent,Vec4& result)
     {
	  result=source+(destination-source)*persent;
     }

     void Interpolator::interpolateAttributeGroup(
	       const ConstAttributeGroupRef& attributeGroupSource, 
	       const ConstAttributeGroupRef& attributeGroupDestination,
	       float percent,AttributeGroupRef& attributeGroupResult,
	       size_t offset)
     {
	  for (int i=offset; i<attributeGroupSource.size(); ++i)
	  {
		    
	       Interpolator::calculate(attributeGroupSource[i], 
			 attributeGroupDestination[i], percent, 
			 attributeGroupResult[i]);
	  }

     }
} /* my_gl */
