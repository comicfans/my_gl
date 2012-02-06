/**
 * one thread one point
 */

//OpenCL 1.1 not support double
typedef struct 
{
     float nearValue;
     float farValue;
     float diff;
} DepthRange;



typedef struct Rectangle{
     int2 xy;
     uint2 widthHeight;
} ViewportParameter/* optional variable list */;


global float4* readAt(size_t idx,
	  global size_t* primitiveIndex,
	  const size_t attributeNumber,
	  const size_t originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes)
{
     size_t vertexIndex=primitiveIndex[idx]; 

     if(vertexIndex>originalSize)
     {
	  return &clipGeneratedAttributes
	       [(vertexIndex-originalSize)*attributeNumber];
     }
     else
     {
	  return &originalVertexAttributes
	       [vertexIndex*attributeNumber];
     }
}

float2 toWinCoord(float2 normalizedDeviceCoordinateXY,
	  const ViewportParameter viewportParameter) 
{
     return normalizedDeviceCoordinateXY*
	  convert_float2(viewportParameter.widthHeight)+
	  convert_float2(viewportParameter.xy);
}

bool outOfRange(uint2 widthHeight,int2 intXY)
{
     return (intXY.x<0) || (intXY.y<0) ||
	  (intXY.x>=widthHeight.s0) || (intXY.y>=widthHeight.s1);
}

/** 
 * @brief map to wincoord,and return the attributeGroup pointer
 * 
 * @param primitiveIndex primitiveIndex of ClippedPrimitiveGroup
 * @param attributeNumber how many attributeNumber in a attributeGroup
 * @param originalSize    how many group is refered by original attributeGroups
 * @param originalVertexAttributes pointer of originalVertexAttributes
 * @param clipGeneratedAttributes  pointer of clip generated vertex attributes
 * @param viewportParameter 
 * @param depthRange
 * 
 * @return attributeGroup processed pointer
 */
float4* pointPreAction(global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes,
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange,
	  global float4 *fragmentAttributeBuffer)
{
     size_t workId;
     workId=get_global_id(0);
     //point index one bye one
     size_t vertexIndex=primitiveIndex[workId];

     global float4* attributeGroup=readAt(vertexIndex,primitiveIndex,attributeNumber
	       ,originalSize,originalVertexAttributes,clipGeneratedAttributes);

     //normalized device coordinates stored in attributeGroup[0]
     attributeGroup[0]/=attributeGroup[0].w;

     //z coordinate mapping
     attributeGroup[0].z*=depthRange.diff;
     attributeGroup[0].z+=depthRange.nearValue;

     //normalized device coordinates -> window coordinates
     attributeGroup[0].xy=toWinCoord
	  (attributeGroup[0].xy,viewportParameter);

     return attributeGroup;
}

kernel void rasterizePointsWithEarlyZ(global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes,
	  //------------ primitive index and data -----------//
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange,
	  global float4* fragmentAttributeBuffer,
	  global float *zBuffer,
	  const uint2 widthHeight)
{
     //not considered half-exit rule yet

     global float4 * attributeGroup=pointPreAction
	  (primitiveIndex,attributeNumber,originalSize,
	   originalVertexAttributes,clipGeneratedAttributes,
	   viewportParameter,depthRange);

     int2 intXY=convert_int2(attributeGroup[0].xy);
     //TODO out of range check, need or needless?

     if(outOfRange(widthHeight,intXY))
     {
	  return;
     }

     //early-z test,only less than is supported

     //--------------------

     //a little confused, x component refers row major ,that is "y" index
     int xyIndex=intXY.s0*widthHeight.x+intXY.s1;

     int reinterpretIntZ=as_int(attributeGroup[0].z);

     global void *temp=zBuffer;
     global int *intZBuffer=temp;
     

     int oldZ=atomic_min(intZBuffer+xyIndex,reinterpretIntZ);

     if(oldZ<=reinterpretIntZ)
     {
	  //z buffer test rejected
	  return;
     }

     //new fragment is generated

     for(int i=0;i<attributeNumber;++i)
     {
	  //copy values
	  fragmentAttributeBuffer[xyIndex+i]=attributeGroup[i];
     }

}

kernel void rasterizeLines()
{
}

kernel void rasterizeTriangles()
{
}

