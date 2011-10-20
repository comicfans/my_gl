/*
 * =====================================================================================
 *
 *       Filename:  Interpolator.hpp
 *
 *    Description:  interpolate between values 
 *
 *        Version:  1.0
 *        Created:  2011-10-9 17:07:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef INTERPOLATOR_HPP

#define INTERPOLATOR_HPP

#include "shader/VertexAttributeBuffer.hpp"

namespace my_gl {

     struct Vec4;
     struct WindowCoordinates;

     class Interpolator {
     public:

	  static void calculate(const Vec4& source,
		    const Vec4& destination,
		    float persent,Vec4& result);


	  static void interpolateAttributeGroup(
	       const ConstAttributeGroupRef& attributeGroupSource, 
	       const ConstAttributeGroupRef& attributeGroupDestination,
	       float percent,AttributeGroupRef& attributeGroupResult,
	       size_t offset=0);


	  virtual ~Interpolator();

	  /** 
	   * @brief which delta of Dim is bigger,
	   * bigger Dim makes percent calculation 
	   * more precision
	   */
	  enum class MajorDim{X,Y};

	  virtual float getPercent(const Vec4& homogenousCoord1,const Vec4& homogenousCoord2,
		const Vec4& normalizedCoord1,const Vec4& normalizedCoord2,
		const WindowCoordinates& winCoord1,
		int majorDelta,
		const WindowCoordinates& toInterpolate,MajorDim majorDim)const;
	
     };
	
} /* my_gl */


#endif /* end of include guard: INTERPOLATOR_HPP */
