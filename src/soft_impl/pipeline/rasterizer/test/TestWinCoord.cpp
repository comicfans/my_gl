/*
 * =====================================================================================
 *
 *       Filename:  TestWinCoord.cpp
 *
 *    Description:  test if wincoord x,y,z in right order
 *
 *        Version:  1.0
 *        Created:  2011-11-1 10:48:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cassert>

#include "WinCoord.hpp"


using namespace my_gl;

int main(int argc, const char *argv[])
{
     int x=2323,y=4532;
     float z=234.2;

     WinCoord coord1(x,y,z);

     assert(coord1.x()==x);
     assert(coord1.y()==y);
     assert(coord1.z()==z);

     WinCoord coord2(coord1);


     assert(coord1.x()==coord2.x());
     assert(coord1.y()==coord2.y());
     assert(coord1.z()==coord2.z());
	
	return 0;
}
