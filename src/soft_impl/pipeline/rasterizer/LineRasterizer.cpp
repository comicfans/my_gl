/*
 * =====================================================================================
 *
 *       Filename:  LineRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-20 21:19:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LineRasterizer.hpp"

#include <functional>

#include "PointRasterizer.hpp"

#include "pipeline/interpolator/Interpolator.hpp"
#include "pipeline/interpolator/CoordInfo.hpp"
#include "shader/FragmentAttributeBuffer.hpp"
#include "LineInfo.hpp"
#include "WinCoord.hpp"




namespace my_gl {

     using std::bind;
     using std::placeholders::_1;


     LineRasterizer::LineRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange)
	       :Rasterizer
		(viewportParameter,interpolator,
		 fragmentAttributeBuffer,depthBuffer,depthRange){}





	template<>
	void LineRasterizer::groupAction<false>
	       (const ConstAttributeGroupRefList& attributeGroupRefs,
		const CoordInfo& coord1,const CoordInfo& coord2,
		const LineInfo& lineInfo,
		const WinCoord& winCoord,
		StepCallback /* ignored */)
	       {
		    auto attributeGroupRef=_fragmentAttributeBuffer
			 .writeNewFragment(winCoord);

		    float percent=_interpolator.getPercent
			 (coord1, coord2,  lineInfo,winCoord);

		    WinCoord rightZ(winCoord.x(),winCoord.y());

		    rightZ.z()=(1-percent)*coord1.windowCoord.z()+
			 percent*coord2.windowCoord.z();

		    if (!earlyZTest(rightZ))
		    {
			 return;
		    }


		    Interpolator::interpolateAttributeGroup
			 (attributeGroupRefs[0], attributeGroupRefs[1], 
			  percent, attributeGroupRef);

		    auto& fragCoord=getVertex(attributeGroupRef);

		    viewportCorrect(fragCoord,rightZ);

		    fragCoord[3]=1.0/fragCoord.w();

	       }

	template<>
	     void LineRasterizer::groupAction<true>
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
		const CoordInfo& coord1,const CoordInfo& coord2,
		const LineInfo& lineInfo,
		const WinCoord& winCoord,
		StepCallback stepCallback)
	     {
		  groupAction<false>(attributeGroupRefs,
			    coord1,coord2,
			    lineInfo,winCoord);
		  stepCallback(winCoord);
	     }

	/** 
	 * @brief rasterize horizontal or vertical line
	 */
	static void rasterizeSpecialImpl(
		  const WinCoord& coord1,
		  const WinCoord& coord2,
		  const LineInfo& lineInfo, 
		  LineRasterizer::StepCallback stepCallback)
	
	{

		    //draw special line
			 
		    WinCoord thisCoord;

		    int majorIndex=int(lineInfo.majorDim),
			nonMajorIndex=int(lineInfo.nonMajorDim);

		    thisCoord[nonMajorIndex]=coord1[nonMajorIndex];


		    for(int majorValue=coord1[majorIndex]+1;
			      majorValue<coord2[majorIndex];
			      ++majorValue)
		    {
			 thisCoord[majorIndex]=majorValue;
			 stepCallback(thisCoord);
		    }
	}


	template<bool hasCallback>
	     void LineRasterizer::rasterizeImpl
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
	      StepCallback stepCallback)
	     {
	       auto 
		    homogenousCoord1=getVertex(attributeGroupRefs[0]),
		  homogenousCoord2=getVertex(attributeGroupRefs[1]);


	       CoordInfo rawCoord1(homogenousCoord1),
			 rawCoord2(homogenousCoord2);

	       rawCoord1.windowCoord=toWinCoord
		    (rawCoord1.normalizedCoord);

	       rawCoord2.windowCoord=toWinCoord
		    (rawCoord2.normalizedCoord);


	       //begin pixel does not need interpolate
	       if (earlyZTest(rawCoord1.windowCoord))
	       {
		    PointRasterizer::rasterizePoint(attributeGroupRefs[0], 
			 _fragmentAttributeBuffer, rawCoord1.windowCoord);
	       }

	       ConstAttributeGroupRefList reorder;

	       int orderIdx[2]={0,1};

	       LineInfo rawLineInfo(rawCoord1.windowCoord,rawCoord2.windowCoord),
			revert(rawLineInfo.revert());

	       auto pCoord1=&rawCoord1,
			 pCoord2=&rawCoord2;
	       auto pLineInfo=&rawLineInfo;

	       //adjust point order,make lineInfo.getMajorDelta always >0 
	       //this makes following rasterize simpler

	       if (rawLineInfo.getMajorDelta()<0)
	       {
		    pLineInfo=&revert;
		    pCoord1=&rawCoord2;
		    pCoord2=&rawCoord1;

		    orderIdx[0]=1;
		    orderIdx[1]=0;
       
	       }
		    reorder.push_back(new ConstAttributeGroupRef
			      (attributeGroupRefs[orderIdx[0]]));
		    reorder.push_back(new ConstAttributeGroupRef
			      (attributeGroupRefs[orderIdx[1]]));
	
	       auto wrappedCallback=bind(
			 &LineRasterizer::groupAction<hasCallback>,
			 this,reorder,
			 *pCoord1,*pCoord2,*pLineInfo,
			 _1,stepCallback);

	       //do not forget the begin pixel 
	       wrappedCallback(rawCoord1.windowCoord);

	       if (rawLineInfo.isOnlyPoint())
	       {
		    //too small
		    //just point, or a segment length less_equal than 1 
		    //gl spec said that 
		    //line segment use half-open draw 
		    //approach,draw beginPoint only
		    //
	           return;
	       }

	       if (rawLineInfo.parallelToAxis())
	       {
		    //horizontal or vertical
		    rasterizeSpecialImpl
			 (pCoord1->windowCoord,pCoord2->windowCoord,
			  *pLineInfo,wrappedCallback);
		    return;
	       }

	       rasterize
		    (pCoord1->windowCoord,pCoord2->windowCoord,
		     *pLineInfo,
		     wrappedCallback);
	
	     }
		
	void LineRasterizer::rasterizeSpecial
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
	      const WinCoord& winCoord1,
	      const WinCoord& winCoord2,
	      const LineInfo& lineInfo)
	{

	     auto 
		    homogenousCoord1=getVertex(attributeGroupRefs[0]),
		  homogenousCoord2=getVertex(attributeGroupRefs[1]);


	       CoordInfo coordInfo1(homogenousCoord1),
			 coordInfo2(homogenousCoord2);

	       coordInfo1.windowCoord=winCoord1;
	       coordInfo2.windowCoord=winCoord2;

	     StepCallback stepCallback=bind(
		       &LineRasterizer::groupAction<false>,this,
		       attributeGroupRefs,
		       coordInfo1,coordInfo2,lineInfo,
		       _1,StepCallback());

	     rasterizeSpecialImpl(winCoord1,winCoord2,lineInfo,stepCallback);
	}

	
     void LineRasterizer::elementRasterize
	  (const ConstAttributeGroupRefList& attributeGroupRefs)
	  {
	       rasterizeImpl<false>(attributeGroupRefs);
	  }

     void LineRasterizer::rasterizeWithCallback
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
		    StepCallback stepCallback)
     {
	  rasterizeImpl<true>(attributeGroupRefs,stepCallback);
     }




     LineRasterizer::~LineRasterizer (){}

} /* my_gl */
