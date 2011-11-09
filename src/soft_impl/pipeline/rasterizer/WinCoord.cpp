/*
 * =====================================================================================
 *
 *       Filename:  WinCoord.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-20 22:25:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "WinCoord.hpp"

#include <cassert>
#include <utility>

namespace my_gl {
	
     using std::make_pair;

     WinCoord::WinCoord(int x,int y,double z)
	  {
	       _xy[0]=x;
	       _xy[1]=y;
	       _z=z;
	  }

	  int& WinCoord::operator[](int index)
	  {
	       assert(index>=0 && index<2);
	       return _xy[index];
	  }

	  const int& WinCoord::operator[](int index)const{
	       assert(index>=0 && index<2);
	       return _xy[index];
	  }

	  int WinCoord::x()const{return _xy[0];}
	  int& WinCoord::x(){return _xy[0];}

	  int WinCoord::y()const{return _xy[1];}
	  int& WinCoord::y(){return _xy[1];}


	  double WinCoord::z()const{return _z;}
	  double & WinCoord::z(){return _z;}

	  bool WinCoord::operator<(const WinCoord& rhs)const
	  {
	       return make_pair(y(),x())<
		    make_pair(rhs.y(),rhs.x());
	  }
} /* my_gl */
