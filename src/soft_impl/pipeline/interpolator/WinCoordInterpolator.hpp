/*
 * =====================================================================================
 *
 *       Filename:  WinCoordInterpolator.hpp
 *
 *    Description:  Interpolate value between window coordinates
 *    simplest Interpolator
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

#ifndef WIN_COORD_INTERPOLATOR_HPP

#define WIN_COORD_INTERPOLATOR_HPP




#include "Interpolator.hpp"

namespace my_gl {

     class WinCoordInterpolator :public Interpolator{
     public:
     	virtual ~WinCoordInterpolator ();
     
     protected:
	  virtual double getPercent(
		    const CoordInfo& coord1,const CoordInfo& coord2,
		    const LineInfo& lineInfo,
		    const WinCoord& toInterpolate)const;
     };
	
} /* my_gl */
#endif /* end of include guard: WIN_COORD_INTERPOLATOR_HPP */
