

typedef struct 
{
     float nearValue;
     float farValue;
     float diff;
} DepthRange;



typedef struct Rectangle{
     int x;
	 int y;
	 uint width;
	 uint height;
     
} ViewportParameter/* optional variable list */;


typedef struct{
uint width;
uint height;
} WidthHeight;


global float4* readAt(size_t idx,
	  global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes)
{

    size_t vertexIndex=primitiveIndex[idx]; 


     if(vertexIndex>=originalSize)
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
     return (normalizedDeviceCoordinateXY+(float2)(1.0f,1.0f))*
	  (float2) (viewportParameter.width,viewportParameter.height) /2 +
	  (float2) (viewportParameter.x,viewportParameter.y);
}

bool outOfRange(WidthHeight widthHeight,int2 intXY)
{
     return (intXY.x<0) || (intXY.y<0) ||
	  (intXY.x>=widthHeight.width) || (intXY.y>=widthHeight.height);
}


global float4* pointPreAction(int idx,
	  global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes,
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange)
{


     global float4* attributeGroup=readAt(idx,primitiveIndex,attributeNumber
	       ,originalSize,originalVertexAttributes,clipGeneratedAttributes);

     attributeGroup[0]/=attributeGroup[0].w;


     attributeGroup[0].z*=depthRange.diff;
     attributeGroup[0].z+=depthRange.nearValue;

     
     attributeGroup[0].xy=toWinCoord
	  (attributeGroup[0].xy,viewportParameter);

     return attributeGroup;
}

bool depthTestAndUpdate(int xyIndex,float thisZValue,global float *zBuffer)
{
     //currently only less than is supported
     global void *temp=zBuffer;
     global int *intZBuffer=temp;
     

     int reinterpretIntZ=as_int(thisZValue);


#ifndef NDEBUG
     global int *pOldZ=intZBuffer+xyIndex;
     if(reinterpretIntZ<*pOldZ)
     {
	  *pOldZ=reinterpretIntZ;
	  return true;
     }
     else
     {
	  return false;
     }

#else
     int oldZ=atomic_min(intZBuffer+xyIndex,reinterpretIntZ);
     return oldZ>reinterpretIntZ;
#endif
}


bool orderTestAndUpdate(int xyIndex,int thisOrder,global int *intZBuffer)
{

     global int *pOldOrder=intZBuffer+xyIndex;
#ifndef NDEBUG
     if(thisOrder>*pOldOrder)
     {
	  *pOldOrder=thisOrder;
	  return true;
     }
     else
     {
	  return false;
     }
#else
     int oldOrder=atomic_max(pOldOrder,thisOrder);
     return oldOrder<thisOrder;
#endif

}

kernel void rasterizePoints(global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes,
	  
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange,
	  global float4* fragmentAttributeBuffer,
	  global int2* activeFragments,
	  global float *zBuffer,
	  const WidthHeight widthHeight)
{

     size_t workId;
     workId=get_global_id(0);
     
  global float4 * attributeGroup=pointPreAction
	  (workId,primitiveIndex,attributeNumber,originalSize,
	   originalVertexAttributes,clipGeneratedAttributes,
	   viewportParameter,depthRange);
	   
     int2 intXY=convert_int2(attributeGroup[0].xy);
     
 
     //write activeFragments
     activeFragments[workId]=intXY;

    

     if(outOfRange(widthHeight,intXY))
     {
	  return ;
     }
     
     int xyIndex=intXY.s0*widthHeight.width+intXY.s1;

#ifdef ENABLE_DEPTH_TEST
     //use early z test
     if(!depthTestAndUpdate(xyIndex,attributeGroup[0].z,zBuffer))
     {
	  return;
     }
#else
     //draw by order,treat zBuffer as atomic order recorde, should init to -INT_MAX
     global void *temp=zBuffer;
     global int* intZBuffer=temp;

     if(!orderTestAndUpdate(xyIndex,get_global_id(0),intZBuffer))
     {
	  return;
     }
#endif//EARLY_Z


     for(int i=0;i<attributeNumber;++i)
     {
	  fragmentAttributeBuffer[xyIndex+i]=attributeGroup[i];
     }

}

kernel void rasterizeLines()
{
}

kernel void rasterizeTriangles()
{
}

