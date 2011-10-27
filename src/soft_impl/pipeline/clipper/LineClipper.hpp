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

     class ClippedPrimitiveGroup;

     class LineClipper :public Clipper{

     public:

     	virtual ~LineClipper ();

	typedef pair<float,float> ClipPercent;

	static bool outOfClipVolume(const ClipPercent& clipResult);

	static ClipPercent mergePercent
	     (const ClipPercent& lhs,const ClipPercent& rhs);

	static bool onlyPoint(const ClipPercent& clipResult);
     
	enum class ClipDim{X,Y,Z};

	static size_t insertInterpolatedAttributes
	     (const ConstAttributeGroupRef& point1Attributes,
	      size_t point1Index,
	      const ConstAttributeGroupRef& point2Attributes,
	      size_t point2Index,
	      float percent,
	      ClippedPrimitiveGroup& clippedPrimitiveGroup);


	static ClipPercent parallelClip
	     (const Vec4& pont1,const Vec4& point2,ClipDim clipDim);


     protected:

	virtual void elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);

     };
	
} /* my_gl */


#endif /* end of include guard: LINE_CLIPPER_HPP */
