/*
 * =====================================================================================
 *
 *       Filename:  testVertexAttributeBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-29 23:33:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "shader/VertexAttributeBuffer.hpp"


using namespace my_gl;

int main(int argc, const char *argv[])
{
     VertexAttributeBuffer buffer;

     buffer.resize(1);

     auto attributeGroup=buffer[0];

     Vec4 vec(0.2,0.3,0.1,0.5);

     attributeGroup[0]=vec;

     assert(vec==attributeGroup[0]);
	
}
