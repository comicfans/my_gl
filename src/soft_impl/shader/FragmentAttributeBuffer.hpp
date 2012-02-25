/*
 * =====================================================================================
 *
 *       Filename:  FragmentAttributeBuffer.hpp
 *
 *    Description:  store rasterized attribute
 *    			VertexAttributeBuffer->FragmentAttributeBuffer use copy approach
 *    			because a few primitive vertex may leads many fragment
 *    			one pixel per slot ,if multi pixel in one slot (same wincoord)
 *    			and early-z buffer test enabled, final fragment is determined
 *    			by pixel which can pass depth test, if depth test disabled
 *    			later reached command drawn pixel is chosen
 *
 *        Version:  1.0
 *        Created:  2011-10-19 9:39:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef FRAGMENT_ATTRIBUTE_BUFFER_HPP

#define FRAGMENT_ATTRIBUTE_BUFFER_HPP

#include <vector>

#include <boost/multi_array.hpp>

#include "common/Vec.hpp"
#include "soft_impl/pipeline/rasterizer/WinCoord.hpp"


namespace my_gl {

     using boost::multi_array;
     using std::vector;

     typedef multi_array<Vec4,3>::reference::reference AttributeGroupRef;
     typedef multi_array<Vec4,3>::const_reference::const_reference ConstAttributeGroupRef;

     class FragmentAttributeBuffer :protected multi_array<Vec4,3>{
     public:

	  typedef multi_array<Vec4,3> SuperType;
     
	  FragmentAttributeBuffer 
	     (size_t width,size_t height,size_t attributeNumber);

	  virtual ~FragmentAttributeBuffer();

	  size_t attributeNumber()const;

	  using SuperType::begin;
	  using SuperType::end;

	  using SuperType::data;

	  AttributeGroupRef writeNewFragment(const WinCoord& winCoord);

	  ConstAttributeGroupRef operator()
	       (const WinCoord& windowCoordinate)const;

	  ConstAttributeGroupRef operator()
	       (size_t y,size_t x)const;


	  size_t width()const;
	       
	  size_t height()const;

	  void clear();

	  //get only active fragments
	  const vector<WinCoord>& getActiveFragWinCoords()const;

     protected:

	  vector<WinCoord> _activeFragWinCoords;

	  bool inRange(const WinCoord& winCoord)const;


     };
	
} /* my_gl */



#endif /* end of include guard: FRAGMENT_ATTRIBUTE_BUFFER_HPP */
