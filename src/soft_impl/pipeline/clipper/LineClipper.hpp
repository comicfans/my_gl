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

     /** 
      * @brief first means min clip point
      * second means max clip point
      */
     typedef pair<float,float> ClipPercent;

     /** 
      * @brief first means if this is infinit point (true= infinit)
      */
     typedef pair<bool,ClipPercent> PackedResult;

     class ClippedPrimitiveGroup;

     class LineClipper :public Clipper{

     public:

     	virtual ~LineClipper ();

	static bool outOfClipVolume(const ClipPercent& clipResult);

	static bool onlyPoint(const ClipPercent& clipResult);
     
	enum class ClipPlane{X,Y,Z};

	static PackedResult commonClip(
		  const Vec4& point1,const Vec4& point2,
		  ClipPlane clipPlane);
     
	static size_t insertInterpolatedAttributes
	     (const ConstAttributeGroupRef& point1Attributes,
	      size_t point1Index,
	      const ConstAttributeGroupRef& point2Attributes,
	      size_t point2Index,
	      float percent,
	      ClippedPrimitiveGroup& clippedPrimitiveGroup,
	      bool hasInfinit);

	static void interpolateAttributeGroup(
	       const ConstAttributeGroupRef& attributeGroupSource, 
	       const ConstAttributeGroupRef& attributeGroupDestination,
	       float percent,AttributeGroupRef& attributeGroupResult,
	       bool hasInfinit=false);
    
     protected:

	virtual void elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);

     };
	
} /* my_gl */


#endif /* end of include guard: LINE_CLIPPER_HPP */
