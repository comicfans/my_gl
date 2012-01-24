/**
 *
 */
kernel void rasterizePoints()
{
}

kernel void rasterizeLines()
{
}

kernel void rasterizeTriangles()
{
}

global float4* readAt(size_t idx,
	  global size_t* primitiveIndex,
	  size_t originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes)
{
     size_t vertexIndex=primitiveIndex[idx]; 

     if(vertexIndex>originalSize)
     {
	  return &clipGeneratedAttributes[vertexIndex-originalSize];
     }
     else
     {
	  return &originalVertexAttributes[vertexIndex];
     }
}

