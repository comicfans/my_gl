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

#include "Interpolator.hpp"

namespace my_gl {

     class WindowCoordinatesInterpolator :public Interpolator{
     public:
     	virtual ~WindowCoordinatesInterpolator ();
     
     protected:
	  virtual double getPercent(
		    const CoordInfo& coord1,const CoordInfo& coord2,
		    const LineInfo& lineInfo,
		    const WindowCoordinates& toInterpolate)const;
     };
	
} /* my_gl */
