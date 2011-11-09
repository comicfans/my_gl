/*
 * =====================================================================================
 *
 *       Filename:  WindowCoordinate.hpp
 *
 *    Description:  a simple typedef
 *
 *        Version:  1.0
 *        Created:  2011-10-20 11:56:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef WIN_COORD_HPP

#define WIN_COORD_HPP



namespace my_gl {

     

     //first is y ,second is x
     struct WinCoord{
	  WinCoord(int x=0,int y=0,double z=0);
	  int& operator[](int index);
	  const int& operator[](int index)const;

	  int y()const;
	  int x()const;
	  double z()const;

	  int& y();
	  int& x();
	  double& z();

	  bool operator<(const WinCoord& rhs)const;

	  private:
	  int _xy[2];
	  double _z;
     } /* optional variable list */;
	
} /* my_gl */

#endif /* end of include guard: WIN_COORD_HPP */
