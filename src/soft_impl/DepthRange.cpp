/*
 * =====================================================================================
 *
 *       Filename:  DepthRange.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 13:35:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "DepthRange.hpp"

namespace my_gl {

     DepthRange::DepthRange(double nearSet,double farSet)
	  :nearValue(nearSet),farValue(farSet){}

     void DepthRange::update()
     {
	  diff=farValue-nearValue;
     }
	
} /* my_gl */
