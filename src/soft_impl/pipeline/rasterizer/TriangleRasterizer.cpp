/*
 * =====================================================================================
 *
 *       Filename:  TriangleRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-21 16:19:31
 *
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
#include <climits>
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

     typedef vector<WinCoord> EdgePoints;

     TriangleRasterizer::TriangleRasterizer
	  (ViewportParameter& viewportParameter,
	   Interpolator& interpolator,
	   FragmentAttributeBuffer& fragmentAttributeBuffer,
	   DepthBuffer& depthBuffer,
	   DepthRange& depthRange,
	   LineRasterizer *pLineRasterizer)
	  :PerElementRasterizer
	   (viewportParameter,interpolator,
	    fragmentAttributeBuffer,depthBuffer,depthRange),
	   _pLineRasterizer(pLineRasterizer)
     {
	  _cullFaceEnabled=false;
	  _frontFaceMode=GL_CCW;
	  _cullFace=GL_BACK;
     }




     TriangleRasterizer::~TriangleRasterizer (){}

     void TriangleRasterizer::setLineRasterizer
	  (LineRasterizer *pLineRasterizer)
	  {
	       _pLineRasterizer=pLineRasterizer;
	  }

     static void append(EdgePoints& edgePoints,
	       const WinCoord& winCoord)
     {
	  edgePoints.push_back(winCoord);
     }

     void TriangleRasterizer::elementRasterize
	  (const ConstAttributeGroupRefList& attributeGroupRefs)
	  {

	       if (isCulled(attributeGroupRefs))
	       {
		    return;
	       }


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


	       if (edgePoints.size()<=3)
	       {
		    //only points no inner region
		    return;
	       }

	       //edge points inserted,dedup same point
	       //sort by y first, x second
	       //after sort,neighbor points is just horizontal lines

	       //remove 
	       sort(edgePoints.begin(),edgePoints.end());


	       //front is smallest y,x
	       //back is biggest y,x

	       //skip point only scan line
	       const int yMin=edgePoints.front().y(),
		     yMax=edgePoints.back().y();

	       auto leftIt=edgePoints.begin();

	       //then do scan line rasterize

	       for(int scanLineY=yMin;
			 scanLineY<=yMax && leftIt<edgePoints.end();
			 ++scanLineY)
	       {

		    auto tryPos=leftIt+1;

		    bool allFinished=false;
		    bool nextLine=false;
		    //this loop search for most inner scan line points
		    //   *    	--------->1) pixel only ,skip
		    //  **	--------->2) pixel is neighbor,skip
		    // * *    	--------->3) normal situation
		    //** * 	--------->4) left pixel is not the most inner one
		    //  **	 
		    //   
		    while(1)
		    {
			 if (tryPos==edgePoints.end())
			 {
			      //top line is point 1)
			      allFinished=true;
			      break;
			 }

			 if (tryPos->y()!=leftIt->y())
			 {
			      //this line is point or situation 2)
			      nextLine=true;
			      leftIt=tryPos;
			      break;
			 }

			 if (tryPos->x()-leftIt->x()<=1)
			 {
			      //neighbor left pixel 4)
			      leftIt=tryPos;
			      ++tryPos;
			      continue;
			 }
			 //same line ,and not neighbor pixel 3)
			 break;
		    }

		    if (allFinished)
		    {
			 break;
		    }

		    if (nextLine)
		    {
			 continue;
		    }

		    assert(leftIt->y()==tryPos->y());
		    assert(leftIt->x()<=tryPos->x());

		    ConstAttributeGroupRefList leftRightAttributes(2);

		    leftRightAttributes.push_back
			 (new ConstAttributeGroupRef(_fragmentAttributeBuffer(*leftIt)));

		    leftRightAttributes.push_back
			 (new ConstAttributeGroupRef(_fragmentAttributeBuffer(*tryPos)));

		    _pLineRasterizer->rasterizeSpecial
			 (leftRightAttributes,*leftIt,*tryPos,
			  //MajorDim=x,delta y=0
			  LineInfo(tryPos->x()-leftIt->x(),0,
			       LineInfo::DimAxis::X));	    

		    leftIt=upper_bound(tryPos,edgePoints.end(),
			      WinCoord(INT_MAX,scanLineY));
	       }

	  }

     bool TriangleRasterizer::isCulled(const 
	       ConstAttributeGroupRefList& attributeGroupRefs)const
     {
	  if (!_cullFaceEnabled)
	  {
	       return false;
	  }

	  else if (_cullFace==GL_FRONT_AND_BACK)
	  {
	       //cull all
	       return true;
	  }

	  WinCoord winCoords[3];

	  for (int i=0; i<3; ++i)
	  {
	       auto & vertex=getVertex(attributeGroupRefs[i]);
	       winCoords[i]=toWinCoord(vertex/vertex.w());
	  }


	  bool positive=areaSignPositive(winCoords);

	  //positive -> towards to reader CCW
	  //negative -> away from reader  CW
	  GLenum faceMode=positive?GL_CCW:GL_CW;

	  return _cullFaceMode==faceMode;
     }
	       void TriangleRasterizer::enableCullFace()
	       {
		    _cullFaceEnabled=true;
	       }

	       void TriangleRasterizer::disableCullFace()
	       {
		    _cullFaceEnabled=false;
	       }

	       void TriangleRasterizer::frontFace(GLenum faceMode)
	       {
		    _frontFaceMode=faceMode;
	       }

	       void TriangleRasterizer::cullFace(GLenum face)
	       {
		    _cullFace=face;
		    if (face==GL_FRONT)
		    {
			 _cullFaceMode=_frontFaceMode;
		    }
		    else if (face==GL_BACK)
		    {
			 if (_frontFaceMode==GL_FRONT)
			 {
			      _cullFaceMode=GL_BACK;
			 }
			 else if(_frontFaceMode==GL_BACK)
			 {
			      _cullFaceMode==GL_FRONT;
			 }
			 else
			 {
			      assert(false ||"wrong face passed");
			 }
		    }
		    _cullFace=face;
	       }


     bool TriangleRasterizer::areaSignPositive
	  (const WinCoord points[3])
	  {
	       float area2Times=0;

	       for (int i=0; i<3; ++i)
	       {
		    int j=(i+1)%3;
		    //cross product makes right hand area
		    float sum=points[i].x()*points[j].y()-
			 points[j].x()*points[i].y();
		    area2Times+=sum;
	       }
	       //sum is 2 times of area
	       return area2Times>0;
	  }


} /* my_gl */
