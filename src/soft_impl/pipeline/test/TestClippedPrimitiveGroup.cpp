/*
 * =====================================================================================
 *
 *       Filename:  TestClippedPrimitiveGroup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-31 12:55:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cassert>
#include "pipeline/ClippedPrimitiveGroup.hpp"
#include "common/test/TestFunction.hpp"

using namespace my_gl;

int main(int argc, const char *argv[])
{
     VertexAttributeBuffer original;

     int randSize=10;
     original.resize(randSize);

     assert(original.elementNumber()==randSize);
     for (int i=0; i<randSize; ++i)
     {
	  for (int j=0; j<VertexAttributeBuffer::DEFAULT_OUT_SIZE; ++j)
	  {
	       original[i][j]=randVec();
	  }
	  
     }

     ClippedPrimitiveGroup clipped(original,PrimitiveMode::POINTS);

     assert(clipped.elementNumber()==0);

     for (int i=0; i<randSize; ++i)
     {
	  clipped.insertOriginalIndex(i);
     }
     assert(clipped.elementNumber()==randSize);

     auto data=clipped.writeClipGeneratedAttribute();

     for (int i=0; i<VertexAttributeBuffer::DEFAULT_OUT_SIZE; ++i)
     {
	  data.second[i]=randVec();
     }

     assert(clipped.elementNumber()==randSize+1);

     ClippedPrimitiveGroup copy(clipped);

     auto& primitiveIndex=copy.getPrimitiveIndex();

     assert(primitiveIndex.vertexNumber()==randSize+1);

     assert(copy.elementNumber()==clipped.elementNumber());

     for (int i:primitiveIndex)
     {
	  assert(copy[i]==clipped[i]);
     }
	
}
