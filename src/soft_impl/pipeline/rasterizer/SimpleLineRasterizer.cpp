/*
 * =====================================================================================
 *
 *       Filename:  SimpleLineRasterizer.cpp
 *
 *    Description:  implementation
 *
 *        Version:  1.0
 *        Created:  2011-10-20 22:14:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SimpleLineRasterizer.hpp"

#include <cmath>

#include "pipeline/interpolator/Interpolator.hpp"
#include "pipeline/interpolator/CoordInfo.hpp"

#include "LineInfo.hpp"

namespace my_gl {



     SimpleLineRasterizer::SimpleLineRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange)
	       :LineRasterizer
		(viewportParameter,interpolator,
		 fragmentAttributeBuffer,depthBuffer,depthRange){}


     SimpleLineRasterizer::~SimpleLineRasterizer(){}

	void SimpleLineRasterizer::rasterize
	     (const WinCoord& coord1,
	      const WinCoord& coord2,
	      const LineInfo& lineInfo,
	      StepCallback stepCallback)
	     {
		  float step=1.0/lineInfo.getMajorDelta();

		  int majorIndex=int(lineInfo.majorDim),
		      nonMajorIndex=int(lineInfo.nonMajorDim);

		  for (int counter=1;counter<lineInfo.getMajorDelta();
			    ++counter)
		  {
		       WinCoord thisCoord;
		       thisCoord[majorIndex]=
			    coord1[majorIndex]+counter;

		       //use simple px=(1-lambda)*p1+lambda*p2;
		       float lambda=step*counter;

		       float anotherValue=(1-lambda)*
			    coord1[nonMajorIndex]+
			    lambda*
			    coord2[nonMajorIndex];

		       thisCoord[nonMajorIndex]=nearbyint(anotherValue);

		       stepCallback(thisCoord);
		  }

	     }

} /* my_gl */
