#include "RasterizerCommon.cl"
#include "TestFunction.cl"


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

#define GenFunc(Name) \
     kernel void Name##RasterizePoints(global uint* primitiveIndex, \
	  const uint attributeNumber, \
	  const uint originalSize, 	\
	  global float4* originalVertexAttributes, \
	  global float4* clipGeneratedAttributes, \
	  const PackedParam packedParam,   \
	  global float *zBuffer, \
	  global float4* fragmentAttributeBuffer, \
	  global int2* activeFragments  )\
{ \
\
     size_t workId;	\
     workId=get_global_id(0);	\
  \
     global float4 * attributeGroup=readAt	\
	  (workId,primitiveIndex,attributeNumber,originalSize,	\
	   originalVertexAttributes,clipGeneratedAttributes);	\
\
     float4 winCoord=toWinCoord(attributeGroup[0],packedParam.viewportParameter,packedParam.depthRange);	\
\
     int2 intXY=convert_int2_rte(winCoord.xy); \
\
\
     if(outOfRange(packedParam.widthHeight,intXY))	\
     {							\
	  activeFragments[workId]=(int2)(-1,-1);		\
	  return ;					\
     }							\
\
     int xyIndex=intXY.s1*packedParam.widthHeight.width+intXY.s0;	\
\
     if(!Name##Test(workId,reinterpretAsIntPtr(zBuffer,xyIndex))) \
     {	\
	  activeFragments[workId]=(int2)(-1,-1);\
	  return;\
     } \
\
     activeFragments[workId]=intXY; \
\
     int beginIndex=xyIndex*attributeNumber;	\
     fragmentAttributeBuffer[beginIndex]=winCoord ;\
\
     for(int i=1;i<attributeNumber;++i) \
     {		\
	  fragmentAttributeBuffer[beginIndex+i]=attributeGroup[i]; \
     }\
\
}

GenFunc(order)
GenFunc(depthLess)
GenFunc(depthLessEqual)
GenFunc(depthGreater)
GenFunc(depthGreaterEqual)
GenFunc(depthEqual)
GenFunc(depthNotEqual)

