/*
 * =====================================================================================
 *
 *       Filename:  TriangleRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-21 16:19:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TriangleRasterizer.hpp"

#include <functional>
#include <vector>
#include <algorithm>

#include "LineRasterizer.hpp"
#include "shader/FragmentAttributeBuffer.hpp"
#include "LineInfo.hpp"

namespace my_gl {


     using std::vector;
     using std::unique;
     using std::bind;
     using std::ref;
     using std::sort;
     using std::placeholders::_1;

     typedef vector<WindowCoordinates> EdgePoints;

     TriangleRasterizer::TriangleRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		LineRasterizer *pLineRasterizer)
	       :Rasterizer
		(viewportParameter,interpolator,fragmentAttributeBuffer),
		_pLineRasterizer(pLineRasterizer)
     {}



     TriangleRasterizer::~TriangleRasterizer (){}

     void TriangleRasterizer::setLineRasterizer
	  (LineRasterizer *pLineRasterizer)
	  {
	       _pLineRasterizer=pLineRasterizer;
	  }


     static bool shortLine
	  (const WindowCoordinates& point1,
	   const WindowCoordinates& point2)
     {
	  if (point1.first!=point2.first)
	  {
	       return false;
	  }
	  //only one pixel offset,no inner line segment
	  return point2.second-point1.second<=1;
     }

     static void append(EdgePoints& edgePoints,
	       const WindowCoordinates& winCoord)
     {
	  edgePoints.push_back(winCoord);
     }

     void TriangleRasterizer::elementRasterize
	  (const ConstAttributeGroupRefList& attributeGroupRefs)
	  {

	       EdgePoints edgePoints;

	       LineRasterizer::StepCallback appendFunc
		    =bind(append,ref(edgePoints),_1);

	       for (int i=0; i<3; ++i)
	       {
	       
		    ConstAttributeGroupRefList edgeAttributes(2);

		    edgeAttributes.push_back(new 
			      ConstAttributeGroupRef(attributeGroupRefs[i]));

		    edgeAttributes.push_back(new
			      ConstAttributeGroupRef(attributeGroupRefs[(i+1)%3]));
		    
		    //use LineRasterizer to rasterize line
		    //and push back edge point to edgePoints

		    _pLineRasterizer->rasterizeWithCallback
			 (edgeAttributes,appendFunc);
	       }


	       //edge points inserted,dedup same point
	       //sort by y first, x second
	       //after sort,neighbor points is just horizontal lines
	       //and no short line(pixel<2)
	       sort(edgePoints.begin(),edgePoints.end());

	       edgePoints.resize(edgePoints.end()-
			 unique(edgePoints.begin(),edgePoints.end(),shortLine));

	       if (edgePoints.size()<=3)
	       {
		    //no inner region
		    return;
	       }

	       //front is smallest y,x
	       //back is biggest y,x

	       int yMin=edgePoints.front().first,
		   yMax=edgePoints.back().first;

	       auto leftIt=edgePoints.begin();
	       
	       //then do scan line rasterize
	       
	       for(int scanLineY=yMin;
			 scanLineY<yMax && leftIt<edgePoints.end();
			 ++scanLineY)
	       {
		    auto rightIt=leftIt+1;
		    if (rightIt==edgePoints.end())
		    {
			 //toppest is a point 
			 break;
		    }

		    if (leftIt->first!=rightIt->first)
		    {
			 //this scan line is a point
			 leftIt=rightIt;
			 continue;
		    }


		    ConstAttributeGroupRefList leftRightAttributes(2);

		    leftRightAttributes.push_back
			 (new ConstAttributeGroupRef(_fragmentAttributeBuffer(*leftIt)));

		    leftRightAttributes.push_back
			 (new ConstAttributeGroupRef(_fragmentAttributeBuffer(*rightIt)));


		    
		    _pLineRasterizer->rasterizeSpecial
			 (leftRightAttributes,*leftIt,*rightIt,
			  //delta y=0,MajorDim=x
			  LineInfo(0,rightIt->second-leftIt->second,LineInfo::DimAxis::X));	    
		    leftIt=rightIt;
	       }

	  }


} /* my_gl */
