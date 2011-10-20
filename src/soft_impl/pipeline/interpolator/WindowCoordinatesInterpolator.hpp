/*
 * =====================================================================================
 *
 *       Filename:  WindowCoordinatesInterpolator.hpp
 *
 *    Description:  Interpolate value between window coordinates
 *
 *        Version:  1.0
 *        Created:  2011-10-20 23:37:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Interpolate.hpp"

namespace my_gl {

     class WindowCoordinatesInterpolator {
     public:
     	virtual ~WindowCoordinatesInterpolator ();
     
     protected:

	  virtual float getPercent(const Vec4& homogenousCoord1,const Vec4& homogenousCoord2,
		const Vec4& normalizedCoord1,const Vec4& normalizedCoord2,
		const WindowCoordinates& winCoord1,
		int majorDelta,
		const WindowCoordinates& toInterpolate,MajorDim majorDim)const
     };
	
} /* my_gl */
