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

     struct CoordInfo;
     struct LineInfo;

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

	  virtual float getPercent(
		    const CoordInfo& coord1,const CoordInfo& coord2,
		    const LineInfo& lineInfo,
		    const WindowCoordinates& toInterpolate)const=0;
	
     };
	
} /* my_gl */


#endif /* end of include guard: INTERPOLATOR_HPP */
