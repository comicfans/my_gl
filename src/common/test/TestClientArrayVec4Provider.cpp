/*
 * =====================================================================================
 *
 *       Filename:  TestClientArrayVec4Provider.cpp
 *
 *    Description:  test if client array vec4 worked
 *
 *        Version:  1.0
 *        Created:  2011-10-30 11:09:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <cassert>
#include "common/ClientArrayVec4Provider.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     float values[2]={0.6,0.2};

     ClientArrayVec4Provider provider(values,2,DataType::FLOAT,0);

     Vec4 readOut=provider.getValue(0);

     assert(readOut==Vec4(0.6,0.2,0,1));
	
     return 0;
}
