#include "RasterizerCommon.cl"
#include "TestFunction.cl"



kernel void orderRasterizeLines(global uint* primitiveIndex, 
	  const uint attributeNumber, 
	  const uint originalSize, 	
	  global float4* originalVertexAttributes, 
	  global float4* clipGeneratedAttributes, 
	  const PackedParam packedParam,   
	  global float *zBuffer, 
	  global float4* fragmentAttributeBuffer, 
	  global int2* activeFragments  ,
	  global int* )
{ 

}
