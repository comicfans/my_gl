/*
 * =====================================================================================
 *
 *       Filename:  Interpolator.hpp
 *
 *    Description:  interpolate between values ,and do 
 *    interpolate between two CoordInfo
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

#include "common/VecFwd.hpp"
#include "shader/VertexAttributeBuffer.hpp"


namespace my_gl {

     struct WinCoord;

     struct CoordInfo;
     struct LineInfo;

     class Interpolator {
     public:

	  /** 
	   * @brief simple linear interpolate,
	   * from source to destination at percent,
	   * write in result 
	   * 
	   * @param source
	   * @param destination
	   * @param percent
	   * @param result
	   */
	  static void calculate(const Vec4& source,
		    const Vec4& destination,
		    double percent,Vec4& result);


	  /** 
	   * @brief interpolate between two group of 
	   * Vec4, with percent ,for every Vec4,
	   * do linear interpolate
	   *
	   * (for further use, offset param is provided
	   * to skip unneeded channel)
	   * 
	   * @param attributeGroupSource
	   * @param attributeGroupDestination
	   * @param percent
	   * @param attributeGroupResult
	   * @param offset
	   */
	  static void interpolateAttributeGroup(
	       const ConstAttributeGroupRef& attributeGroupSource, 
	       const ConstAttributeGroupRef& attributeGroupDestination,
	       double percent,AttributeGroupRef& attributeGroupResult,
	       size_t offset=0);


	  virtual ~Interpolator();

	  virtual double getPercent(
		    const CoordInfo& coord1,const CoordInfo& coord2,
		    const LineInfo& lineInfo,
		    const WinCoord& toInterpolate)const=0;
	
     };
	
} /* my_gl */


#endif /* end of include guard: INTERPOLATOR_HPP */
