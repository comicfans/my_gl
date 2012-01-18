/*
 * =====================================================================================
 *
 *       Filename:  PerElementRasterizer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-18 14:16:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PER_ELEMENT_RASTERIZER_HPP

#define PER_ELEMENT_RASTERIZER_HPP

#include "Rasterizer.hpp"

namespace my_gl {

     /** 
      * @brief rasterize element one by one 
      *  	(function is one element rasterize,can be execute 
      *  	in parall)
      *  	sub class show override elementRasterize function 
      *  	to implement 
      */
     class PerElementRasterizer :public Rasterizer{
	  public:
	       PerElementRasterizer 
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange);


	       virtual void rasterize(
			 const ClippedPrimitiveGroup& clippedPrimitiveGroup);

	       virtual ~PerElementRasterizer ();
	  protected:

	       /** 
		* @brief per-element rasterize,such as 
		* point/line segment/triangle
		* super class function rasterize use the 
		* primitive information of PrimitiveIndex
		* to determine how many vertex should be 
		* grouped as a element
		* 
		* @param attributeGroupRefs attributeGroup of element vertex
		* @param fragmentAttributeBuffer buffer to write fragment input
		* 
		* @return 
		*/
	       virtual void elementRasterize
		    (const ConstAttributeGroupRefList& attributeGroupRefs)=0;


     };

} /* my_gl */


#endif /* end of include guard: PER_ELEMENT_RASTERIZER_HPP */
