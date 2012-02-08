/*
 * =====================================================================================
 *
 *       Filename:  Clipper.hpp
 *
 *    Description:  interface to clip primitive
 *
 *        Version:  1.0
 *        Created:  2011-10-9 20:51:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CLIPPER_HPP

#define CLIPPER_HPP



#include "soft_impl/shader/VertexAttributeBuffer.hpp"
#include <boost/ptr_container/ptr_vector.hpp>


namespace my_gl {


     using boost::ptr_vector;

     typedef ptr_vector<ConstAttributeGroupRef> 
	  ConstAttributeGroupRefList;

     class ClippedPrimitiveGroup;
     class PrimitiveIndex;

     class Clipper {
     public:

	  virtual ~Clipper ();

	  /** 
	   * @brief 
	   * 
	   * @param projectedDataBuffer 
	   * all vertex data comes from vertex shader
	   *
	   * @param originalPrimitiveIndex
	   * PrimitiveIndex which ref all vertex shader data
	   * @param clippedPrimitiveGroup
	   * clip result,contains new vertex data and complete
	   * index of these vertex data
	   * 
	   * @return 
	   */
	  void clip
	       (const VertexAttributeBuffer& projectedDataBuffer,
		const PrimitiveIndex& originalPrimitiveIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);

     protected:


	  /** 
	   * @brief single element clip 
	   * all needed vertex data is stored in attributeGroupRefs
	   * (in order of drawing command)
	   * and these vertex index of all vertex output data
	   * is stored in vertexIndex,use these index to 
	   * optimize output data(ClippedPrimitiveGroup holds a 
	   * reference of all vertex output data,only store clip 
	   * generated vertex data ,original vertex only stores a 
	   * index)
	   * 
	   * @param attributeGroupRefs
	   * @param vertexIndex
	   * @param clippedPrimitiveGroup
	   * 
	   * @return 
	   */
	  virtual void elementClip
	       (const ConstAttributeGroupRefList& attributeGroupRefs,
		const size_t *vertexIndex,
	       ClippedPrimitiveGroup& clippedPrimitiveGroup)=0;


    
     };
	
} /* my_gl */


#endif /* end of include guard: CLIPPER_HPP */
