/*
 * =====================================================================================
 *
 *       Filename:  FragmentAttributeBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-19 10:28:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "FragmentAttributeBuffer.hpp"

#include <array>

namespace my_gl {
     using std::array;
     using boost::extents;

     const int SIDE_OFFSET=1;

     FragmentAttributeBuffer::FragmentAttributeBuffer 
	  (size_t width,size_t height,size_t attributeNumber)
	  :SuperType(extents[height+SIDE_OFFSET]
		    [width][attributeNumber])
     {
	  //clipped coordinates may be out of clip volume a little
	  //so makes FragmentAttributeBuffer a little outter
	  //if writeNewFragment is called with WinCoord out of range
	  //just return a dummy vec4 group ([-1][0])
	  //
	  array<int,3> bases={-SIDE_OFFSET,0,0};
	  reindex(bases);
     }

     bool FragmentAttributeBuffer::inRange
	  (const WinCoord& winCoord)const
     {
	  return winCoord.y()>=0 && winCoord.y()<height()
	       &&winCoord.x()>=0&& winCoord.x()<width();
     }

     AttributeGroupRef FragmentAttributeBuffer::writeNewFragment(
	       const WinCoord& winCoord)
     {
	  if (inRange(winCoord))
	  {
	       _activeFragWinCoords.push_back(winCoord);
	       return (*this)[winCoord.y()][winCoord.x()];
	  }

	  return (*this)[-SIDE_OFFSET][0];
     }

     ConstAttributeGroupRef FragmentAttributeBuffer::operator()
	  (size_t x,size_t y)const
	  {
	       return (*this)[y][x];

	  }
     ConstAttributeGroupRef FragmentAttributeBuffer::operator()
	  (const WinCoord& windowCoordinate)const
	  {
	       return (*this)
		    (windowCoordinate.x(),windowCoordinate.y());

	  }
     size_t FragmentAttributeBuffer::
	  attributeNumber()const
	  {
	       return shape()[2];
	  }

     size_t FragmentAttributeBuffer::width()const
     {
	  return shape()[1]-SIDE_OFFSET*2;
     }
     size_t FragmentAttributeBuffer::height()const
     {
	  return shape()[0]-SIDE_OFFSET*2;
     }

     void FragmentAttributeBuffer::clear()
     {
	  _activeFragWinCoords.clear();
     }

     const vector<WinCoord>& FragmentAttributeBuffer
	  ::getActiveFragWinCoords()const
	  {
	       return _activeFragWinCoords;
	  }
} /* my_gl */
