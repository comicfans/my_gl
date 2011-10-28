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
		FragmentAttributeBuffer& fragmentAttributeBuffer);


	
	  void rasterizeSpecial(
		  ConstAttributeGroupRef* attributeGroupRefs,
		  const WindowCoordinates& winCoord1,
		  const WindowCoordinates& winCoord2,
		  const LineInfo& lineInfo);
	
	  /** 
	   * @brief call this function to tell callee
	   * a new window pixel is generated
	   */
	  typedef function<void(const WindowCoordinates&)> StepCallback;

	 
	  virtual ~LineRasterizer ();

	  void rasterizeWithCallback(
		    ConstAttributeGroupRef* attributeGroupRefs,
		    StepCallback stepCallback);

     protected:



	virtual void elementRasterize
	       (ConstAttributeGroupRef* attributeGroupRefs);

	template<bool hasCallback=false>
	     void rasterizeImpl
	     (ConstAttributeGroupRef* attributeGroupRefs,
	      StepCallback stepCallback=StepCallback());

	virtual void rasterize
	     (const WindowCoordinates& winCoord1,
	      const WindowCoordinates& winCoord2,
	      const LineInfo& lineInfo,
	      StepCallback stepCallback)=0;



     private:

	template<bool hasCallback=false>
	void groupAction
	       (ConstAttributeGroupRef* attributeGroupRefs,
		const CoordInfo& coordInfo1,const CoordInfo& coordInfo2,
		const LineInfo& lineInfo,
		const WindowCoordinates& winCoord,
		StepCallback stepCallback=StepCallback());


     };
	
} /* my_gl */


#endif /* end of include guard: LINE_RASTERIZER_HPP */