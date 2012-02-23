

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


global float4* pointPreAction(global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes,
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange)
{


     size_t workId;
     workId=get_global_id(0);



	 
     global float4* attributeGroup=readAt(0,primitiveIndex,attributeNumber
	       ,originalSize,originalVertexAttributes,clipGeneratedAttributes);

     attributeGroup[0]/=attributeGroup[0].w;


     attributeGroup[0].z*=depthRange.diff;
     attributeGroup[0].z+=depthRange.nearValue;

     
     attributeGroup[0].xy=toWinCoord
	  (attributeGroup[0].xy,viewportParameter);

     return attributeGroup;
}

bool earlyZTestAndUpdate(int xyIndex,float thisZValue,global float *zBuffer)
{

     

     global void *temp=zBuffer;
     global int *intZBuffer=temp;
     

     int reinterpretIntZ=as_int(thisZValue);

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

     //int oldZ=atomic_min(intZBuffer+xyIndex,reinterpretIntZ);
     //return oldZ>reinterpretIntZ;
}


bool orderTestAndUpdate(int xyIndex,int thisOrder,global int *intZBuffer)
{
     global int *pOldOrder=intZBuffer+xyIndex;

     if(thisOrder>*pOldOrder)
     {
	  *pOldOrder=thisOrder;
	  return true;
     }
     else
     {
	  return false;
     }

     //int oldOrder=atomic_max(intZBuffer+xyIndex,thisOrder);
     //return oldOrder<thisOrder;

}

kernel void rasterizePointsByOrder(global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes,
	  
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange,
	  global float4* fragmentAttributeBuffer,
	  global float *zBuffer,
	  const WidthHeight widthHeight)
{
     

     global float4 * attributeGroup=pointPreAction
	  (primitiveIndex,attributeNumber,originalSize,
	   originalVertexAttributes,clipGeneratedAttributes,
	   viewportParameter,depthRange);

     int2 intXY=convert_int2(attributeGroup[0].xy);
     
     

     if(outOfRange(widthHeight,intXY))
     {
	  return ;
     }

     
     int xyIndex=intXY.s0*widthHeight.width+intXY.s1;

     global void *temp=zBuffer;
     global int* intZBuffer=temp;

     if(!orderTestAndUpdate(xyIndex,get_global_id(0),intZBuffer))
     {
	  return;
     }

     
     for(int i=0;i<attributeNumber;++i)
     {
	  fragmentAttributeBuffer[xyIndex+i]=attributeGroup[i];
     }

}

kernel void rasterizePointsWithEarlyZ(global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes,
	  
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange,
	  global float4* fragmentAttributeBuffer,
	  global float *zBuffer,
	  const WidthHeight widthHeight)
{
     
  global float4 * attributeGroup=pointPreAction
	  (primitiveIndex,attributeNumber,originalSize,
	   originalVertexAttributes,clipGeneratedAttributes,
	   viewportParameter,depthRange);
	   
     int2 intXY=convert_int2(attributeGroup[0].xy);
     
     

     if(outOfRange(widthHeight,intXY))
     {
	  return ;
     }

     
     int xyIndex=intXY.s0*widthHeight.width+intXY.s1;

     if(!earlyZTestAndUpdate(xyIndex,attributeGroup[0].z,zBuffer))
     {
	  return;
     }

     
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

