#include "RasterizerCommon.cl" 

/** 
 * @brief calculate the length of lines, vertex data is stored as GL_LINES format
 *	(two vertex grouped together as a line)
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
kernel void preprocessLines(global uint* primitiveIndex, 
	  const uint attributeNumber, 
	  const uint originalSize, 	
	  global float4* originalVertexAttributes, 
	  global float4* clipGeneratedAttributes,
	  const PackedParam packedParam,
	  int *linesLength)
{
     int workId;
     workId=get_global_id(0);

     global float4* vertex1AttributeGroup=readAt(workId*2,primitiveIndex,attributeNumber,
	       originalSize,originalVertexAttributes,clipGeneratedAttributes);

     global float4 *vertex2AttributeGroup=readAt(workId*2+1,primitiveIndex,attributeNumber,
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
	
/** 
 * @brief calculate the length of lines, vertex data is stored as GL_LINE_STRIP format
 *	(a vertex followed by leading one grouped together as a line)
 *        a line per thread
 * 
 * 
 * @param primitiveIndex
 * @param attributeNumber
 * @param originalSize
 * @param originalVertexAttributes
 * @param clipGeneratedAttributes
 * @param packedParam
 * @param linesLength
 * 
 * @return 
 */
kernel void preprocessLineStrip(global uint* primitiveIndex, 
	  const uint attributeNumber, 
	  const uint originalSize, 	
	  global float4* originalVertexAttributes, 
	  global float4* clipGeneratedAttributes,
	  const PackedParam packedParam,
	  int *linesLength)
{
     int workId;
     workId=get_global_id(0);

     global float4* vertex1AttributeGroup=readAt(workId*2,primitiveIndex,attributeNumber,
	       originalSize,originalVertexAttributes,clipGeneratedAttributes);

     global float4 *vertex2AttributeGroup=readAt(workId*2+1,primitiveIndex,attributeNumber,
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
	
