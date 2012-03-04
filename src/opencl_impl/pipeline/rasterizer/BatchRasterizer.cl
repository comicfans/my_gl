#include "RasterizerCommon.cl"
#include "TestFunction.cl"

	

template<class T>
     kernel void TRasterizePoints(global uint* primitiveIndex, 
	  const uint attributeNumber, 
	  const uint originalSize, 	
	  global float4* originalVertexAttributes, 
	  global float4* clipGeneratedAttributes, 
	  const PackedParam packedParam,   
	  global float *zBuffer, 
	  global float4* fragmentAttributeBuffer, 
	  global int2* activeFragments  )
{ 

     size_t workId;	
     workId=get_global_id(0);	
  
     global float4 * attributeGroup=readAt	
	  (workId,primitiveIndex,attributeNumber,originalSize,	
	   originalVertexAttributes,clipGeneratedAttributes);	

     float4 winCoord=toWinCoord(attributeGroup[0],packedParam.viewportParameter,packedParam.depthRange);	

     int2 intXY=convert_int2_rte(winCoord.xy); 


     if(outOfRange(packedParam.widthHeight,intXY))	
     {							
	  activeFragments[workId]=(int2)(-1,-1);		
	  return ;					
     }							

     int xyIndex=intXY.s1*packedParam.widthHeight.width+intXY.s0;	

     if(!T::test(workId,reinterpretAsIntPtr(zBuffer,xyIndex))) 
     {	
	  activeFragments[workId]=(int2)(-1,-1);
	  return;
     } 

     activeFragments[workId]=intXY; 

     int beginIndex=xyIndex*attributeNumber;	
     fragmentAttributeBuffer[beginIndex]=winCoord ;

     for(int i=1;i<attributeNumber;++i) 
     {		
	  fragmentAttributeBuffer[beginIndex+i]=attributeGroup[i]; 
     }

}

template 
__attribute__((mangled_name(orderRasterizePoints))) kernel void 
TRasterizePoints<OrderTest>(global uint* , const uint , const uint , global float4* , 
	  global float4* ,const PackedParam ,  global float *, global float4* , global int2* );

template 
__attribute__((mangled_name(depthLessRasterizePoints))) kernel void 
TRasterizePoints<LessTest>(global uint* , const uint , const uint , global float4* , 
	  global float4* ,const PackedParam ,  global float *, global float4* , global int2* );

template 
__attribute__((mangled_name(depthLessEqualRasterizePoints))) kernel void 
TRasterizePoints<LessEqualTest>(global uint* , const uint , const uint , global float4* , 
	  global float4* ,const PackedParam ,  global float *, global float4* , global int2* );

template 
__attribute__((mangled_name(depthGreaterEqualRasterizePoints))) kernel void 
TRasterizePoints<GreaterEqualTest>(global uint* , const uint , const uint , global float4* , 
	  global float4* ,const PackedParam ,  global float *, global float4* , global int2* );

template 
__attribute__((mangled_name(depthEqualRasterizePoints))) kernel void 
TRasterizePoints<EqualTest>(global uint* , const uint , const uint , global float4* , 
	  global float4* ,const PackedParam ,  global float *, global float4* , global int2* );

template 
__attribute__((mangled_name(depthNotEqualRasterizePoints))) kernel void 
TRasterizePoints<NotEqualTest>(global uint* , const uint , const uint , global float4* , 
	  global float4* ,const PackedParam ,  global float *, global float4* , global int2* );


