/*
 * =====================================================================================
 *
 *       Filename:  TestLineInfo.cpp
 *
 *    Description:  test revert function
 *
 *        Version:  1.0
 *        Created:  2011-11-1 10:53:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cassert>

#include "pipeline/rasterizer/LineInfo.hpp"



using namespace my_gl;

int main(int argc, const char *argv[])
{
     LineInfo lineInfo(234,23,LineInfo::DimAxis::X);

     LineInfo shouldSame(lineInfo.revert().revert());

     assert(lineInfo.getMajorDelta()==shouldSame.getMajorDelta());
     assert(lineInfo.deltaX==shouldSame.deltaX);
     assert(lineInfo.deltaY==shouldSame.deltaY);
	
	return 0;
}
