/*
 * =====================================================================================
 *
 *       Filename:  LineClipper.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-11 11:24:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LINE_CLIPPER_HPP

#define LINE_CLIPPER_HPP

#include <utility>

#include "Clipper.hpp"


namespace my_gl {

     using std::pair;

     typedef std::pair<float,float> ClipPercent;



     class LineClipper :public Clipper{

     public:

     	virtual ~LineClipper ();



	/** 
	 * @brief Liang-Barsky clip algorithm work only with in 
	 * normalized device coordinates [-1,1]
	 * 
	 * @param first firs point
	 * @param second second point 
	 * @param crossPlane which plane to get intersect
	 * 
	 * @return a parameterize percent pair, should first<=second
	 * if first>second ,this line lies totally out of clip volume
	 */
	static ClipPercent clipLiangBarsky(const Vec4& point1,
		  const Vec4& point2);

	/** 
	 * @brief clip in homogenous coordinates,work 
	 * in all situation
	 * 
	 * @param point1
	 * @param point2
	 * 
	 * @return 
	 */
	static ClipPercent clipInHomogenousCoordinates
	     (const Vec4& point1,const Vec4& point2);

	static bool outOfClipVolume(const ClipPercent& clipResult);

     protected:

	void lineClipImpl();

	template<bool NeedPerspectiveDivision>
	     void interpolateAttributeGroup
	     
	     (
		  const ConstAttributeGroupRef& attributeGroupSource,
		  const ConstAttributeGroupRef& attributeGroupDestination,
		  float percent, AttributeGroupRef& AttributeGroupResult
		  );

	  virtual void elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);




     };
	
} /* my_gl */


#endif /* end of include guard: LINE_CLIPPER_HPP */
