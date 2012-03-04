
/** 
 * @brief fp64 is an extension 
 *  not support by many device
 */
typedef struct 
{
     float nearValue;
     float farValue;
     float diff;
} DepthRange ;



typedef struct {
     int x;
	 int y;
	 uint width;
	 uint height;
     
} ViewportParameter ;


typedef struct{
int width;
int height;
} WidthHeight ;

/** 
 * @brief pack three struct together. there is bug in AMD ocl
 *       runtime, all struct parameter can not be passed in 
 *	 correctly except first one
 */
typedef struct {
     ViewportParameter viewportParameter;
     DepthRange depthRange;
     WidthHeight widthHeight;
} PackedParam;



/** 
 * @brief read attributeGroup from clippedPrimitiveGroup by vertexIndex 
 * 
 * @param idx index of primitiveIndex
 * @param primitiveIndex indirect vertex index array
 * @param attributeNumber 
 * @param originalSize originalVertexAttributes (all, include clipped) vertex attribute group number
 * @param originalVertexAttributes raw vertex attributes passed from OpenGL API (glVertexPointer)
 * @param clipGeneratedAttributes 
 * 
 * @return vertex attribute group at specified idx (of primitiveIndex)
 */
global float4* readAt(size_t idx,
	  global uint* primitiveIndex,
	  const uint attributeNumber,
	  const uint originalSize,
	  global float4* originalVertexAttributes,
	  global float4* clipGeneratedAttributes)
{

     //get indirect real vertex index
    size_t vertexIndex=primitiveIndex[idx]; 


    //check if this vertex index belong to originalVertexAttributes
     if(vertexIndex>=originalSize)
     {
	  return clipGeneratedAttributes+
	       (vertexIndex-originalSize)*attributeNumber;
     }
     else
     {
	  return originalVertexAttributes+
	       vertexIndex*attributeNumber;
     }
}

/** 
 * @brief map normalized Device Coordinate XY [-1,1] to windows coordinate by viewportParameter
 * 
 * @param normalizedDeviceCoordinateXY
 * @param viewportParameter
 * 
 * @return windows coord in float (to keep percision ,int convertion can be done later)
 */
float4 toWinCoord(float4 clippedCoord,
	  const ViewportParameter viewportParameter,
	  const DepthRange depthRange) 
{
     clippedCoord/=clippedCoord.w;


     clippedCoord.xy=(clippedCoord.xy+(float2)(1.0f,1.0f))*
	  (float2) (viewportParameter.width,viewportParameter.height) /2 +
	  (float2) (viewportParameter.x,viewportParameter.y);

     clippedCoord.z*=depthRange.diff;
     clippedCoord.z+=depthRange.nearValue;

     return clippedCoord;
}


/** 
 * @brief check if windows Coordinate is out of real window range. after primitive clip
 * 		position near window edge can be a little out of [-1,1] (float error)
 *		so second check is neccessry
 * 
 * @param widthHeight real windows size
 * @param intXY 	windows coordinate
 * 
 * @return 
 */
bool outOfRange(WidthHeight widthHeight,int2 intXY)
{
     return (intXY.x<0) || (intXY.y<0) ||
	  (intXY.x>=widthHeight.width) || (intXY.y>=widthHeight.height);
}


/** 
 * @brief this function used to reinterpret float pointer and offset to int*
 *        for atomic use
 * 
 * @param pFloat pointer to float array
 * @param offset 
 * 
 * @return interpret pFloat+offset as int*
 */
global int* reinterpretAsIntPtr(global float* pFloat,int offset)
{
     return ((global int*)((global void*)pFloat))+offset;
}
