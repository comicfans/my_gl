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


/** 
 * @brief calculate the length of lines
 *	class template is GL_LINES (two vertex grouped together as a line)
 *			  GL_LINE_STRIP()
 *        a line per thread
 * 
 * @param primitiveIndex
 * @param attributeNumber
 * @param originalSize
 * @param originalVertexAttributes
 * @param clipGeneratedAttributes
 * 
 * @return 
 */
template <class T>
kernel void preprocessTSegments(global uint* primitiveIndex, 
	  const uint attributeNumber, 
	  const uint originalSize, 	
	  global float4* originalVertexAttributes, 
	  global float4* clipGeneratedAttributes,
	  const PackedParam packedParam,
	  int *linesLength)
{
     int workId;
     workId=get_global_id(0);

     int2 vertexIndex=T::getIndex(workId),

     global float4* vertex1AttributeGroup=readAt(vertexIndex.s0,primitiveIndex,attributeNumber,
	       originalSize,originalVertexAttributes,clipGeneratedAttributes);

     global float4 *vertex2AttributeGroup=readAt(vertexIndex.s1,primitiveIndex,attributeNumber,
	       originalSize,originalVertexAttributes,clipGeneratedAttributes);

     float4 vertex1WinCoord=toWinCoord(vertex1AttributeGroup[0],
	       packedParam.viewportParameter,packedParam.depthRange),
	    vertex2WinCoord=toWinCoord(vertex2AttributeGroup[1],
		      packedParam.viewportParameter,packedParam.depthRange);

     int2 vertex1XY=convert_int2_rte(vertex1WinCoord.xy),
	  vertex2XY=convert_int2_rte(vertex2WinCoord.xy);

     int2 lineVector=vertex1XY-vertex2XY;

     linesLength[workId]=max(abs(lineVector.x),abs(lineVector.y));
}
	
template 
__attribute__((mangled_name(preprocessLineStripSegments))) kernel void preprocessTSegments<LineStripIndex>
(global uint* , const uint , const uint , global float4* , global float4* ,const PackedParam ,int *)
	
template 
__attribute__((mangled_name(preprocessLinesSegments))) kernel void preprocessTSegments<LineIndex>
(global uint* , const uint , const uint , global float4* , global float4* ,const PackedParam ,int *)

