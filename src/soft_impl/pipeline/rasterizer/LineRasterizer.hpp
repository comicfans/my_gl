/*
 * =====================================================================================
 *
 *       Filename:  LineRasterizer.hpp
 *
 *    Description:  common interface of LineRasterizer
 *
 *        Version:  1.0
 *        Created:  2011-10-20 20:20:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LINE_RASTERIZER_HPP

#define LINE_RASTERIZER_HPP

#include <functional>

#include "PerElementRasterizer.hpp"

namespace my_gl {

     using std::function;

     struct CoordInfo;

     struct LineInfo;

     /** 
      * @brief Rasterizer to do line rasterize
      */
     class LineRasterizer :public PerElementRasterizer{
     public:

	  /** 
	   * @brief construct with some basic parameter
	   * 
	   * @param viewportParameter
	   * @param interpolator
	   * @param fragmentAttributeBuffer
	   * @param depthBuffer used as early-Z test
	   * @param depthRange used as normalized 
	   * 
	   * @return 
	   */
	  LineRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange);
	
	
	  /** 
	   * @brief rasterize vertical or horizontal line from
	   *        two wincoord points .
	   *        points must be in vertical or horizontal line
	   *        or will rise a assert, left-right or up-down point
	   *        can appear in right or reverted order, function
	   *        can reorder this
	   * 
	   * @param attributeGroupRefs all attributes of two ending point
	   * @param winCoord1 point1 winCoord
	   * @param winCoord2 point2 winCoord
	   * @param lineInfo the LineInfo(with majorDelta and majorAxis)
	   */
	  void rasterizeSpecial(
		    const ConstAttributeGroupRefList& attributeGroupRefs,
		  const WinCoord& winCoord1,
		  const WinCoord& winCoord2,
		  const LineInfo& lineInfo);
	
	  /** 
	   * @brief call this function to tell callee
	   * 	     a new window pixel is generated
	   */
	  typedef function<void(const WinCoord&)> StepCallback;

	 
	  virtual ~LineRasterizer ();

	  /** 
	   * @brief wrap call of rasterizeImpl<true>
	   * 
	   * @param attributeGroupRefs
	   * @param stepCallback
	   */
	  void rasterizeWithCallback(
		    const ConstAttributeGroupRefList& attributeGroupRefs,
		    StepCallback stepCallback);

     protected:



	virtual void elementRasterize
	       (const ConstAttributeGroupRefList& attributeGroupRefs);

	template<bool hasCallback=false>
	     /** 
	      * @brief rasterize from attributeGroups,extract WinCoord
	      * 	from AttributeGroup , and call 
	      * 	rasterize(WinCoord,WinCoord,LineInfo,StepCallback)
	      * 	internal. StepCallback will bypass to 
	      * 	rasterize(WinCoord,WinCoord,LineInfo,StepCallback)
	      * 	when new pixel is generated, StepCallback will be 
	      * 	called(if template parameter==true)
	      * 
	      * @param attributeGroupRefs attributeGroupRefs of two points
	      * @param stepCallback if template parameter hasCallback==true
	      * 			will call StepCallback , or 
	      * 			StepCallback will be ignored 
	      * @return 
	      */
	     void rasterizeImpl
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
	      StepCallback stepCallback=StepCallback());

	/** 
	 * @brief rasterize from two WinCoords
	 * 	  with StepCallback, override this 
	 * 	  function to implement different line 
	 * 	  rasterize algorithm
	 * 
	 * @param winCoord1
	 * @param winCoord2
	 * @param lineInfo
	 * @param stepCallback
	 * 
	 * @return 
	 */
	virtual void rasterize
	     (const WinCoord& winCoord1,
	      const WinCoord& winCoord2,
	      const LineInfo& lineInfo,
	      StepCallback stepCallback)=0;



     private:

	template<bool hasCallback=false>
	     /** 
	      * @brief when rasterize a line,
	      * 
	      * @param attributeGroupRefs
	      * @param coordInfo1
	      * @param coordInfo2
	      * @param lineInfo
	      * @param winCoord
	      * @param stepCallback
	      */
	void groupAction(
		  const ConstAttributeGroupRefList& attributeGroupRefs,
		const CoordInfo& coordInfo1,const CoordInfo& coordInfo2,
		const LineInfo& lineInfo,
		const WinCoord& winCoord,
		StepCallback stepCallback=StepCallback());


     };
	
} /* my_gl */


#endif /* end of include guard: LINE_RASTERIZER_HPP */
