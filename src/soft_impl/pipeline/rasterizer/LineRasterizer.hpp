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

#include "Rasterizer.hpp"

namespace my_gl {

     using std::function;

     struct CoordInfo;

     struct LineInfo;

     class LineRasterizer :public Rasterizer{
     public:

	  LineRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange);
	


	
	  void rasterizeSpecial(
		    const ConstAttributeGroupRefList& attributeGroupRefs,
		  const WinCoord& winCoord1,
		  const WinCoord& winCoord2,
		  const LineInfo& lineInfo);
	
	  /** 
	   * @brief call this function to tell callee
	   * a new window pixel is generated
	   */
	  typedef function<void(WinCoord&)> StepCallback;

	 
	  virtual ~LineRasterizer ();

	  void rasterizeWithCallback(
		    const ConstAttributeGroupRefList& attributeGroupRefs,
		    StepCallback stepCallback);

     protected:



	virtual void elementRasterize
	       (const ConstAttributeGroupRefList& attributeGroupRefs);

	template<bool hasCallback=false>
	     void rasterizeImpl
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
	      StepCallback stepCallback=StepCallback());

	virtual void rasterize
	     (const WinCoord& winCoord1,
	      const WinCoord& winCoord2,
	      const LineInfo& lineInfo,
	      StepCallback stepCallback)=0;



     private:

	template<bool hasCallback=false>
	void groupAction(
		  const ConstAttributeGroupRefList& attributeGroupRefs,
		const CoordInfo& coordInfo1,const CoordInfo& coordInfo2,
		const LineInfo& lineInfo,
		WinCoord& winCoord,
		StepCallback stepCallback=StepCallback());


     };
	
} /* my_gl */


#endif /* end of include guard: LINE_RASTERIZER_HPP */
