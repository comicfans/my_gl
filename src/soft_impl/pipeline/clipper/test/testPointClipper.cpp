/*
 * =====================================================================================
 *
 *       Filename:  testPointClipper.cpp
 *
 *    Description:  test if point in clip volume
 *
 *        Version:  1.0
 *        Created:  2011-10-26 13:46:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <cassert>
#include "pipeline/clipper/PointClipper.hpp"
#include "common/Vec.hpp"

using namespace my_gl;
int main(int argc, const char *argv[])
{
     Vec4 shouldIn[]={{1,2,3,4},
	  {1,1,1,1},{0,3,2,9},{0.5,0.3,0.2,0.5}};

     for(auto& one:shouldIn)
     {
	  assert(PointClipper::inClipVolume(one));
     }


     Vec4 shouldOut[]={
	  {1.2,1,1,1},{2,2,2,1},
	  {0,0,4,0},{9,3,2,8}};

     for(auto& one:shouldOut)
     {
	  assert(!PointClipper::inClipVolume(one));
     }
	
}
