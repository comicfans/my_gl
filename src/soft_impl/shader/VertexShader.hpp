/*
 * =====================================================================================
 *
 *       Filename:  VertexShader.hpp
 *
 *    Description:  vertex shader
 *
 *        Version:  1.0
 *        Created:  2011-9-28 20:24:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VERTEX_SHADER_HPP

#define VERTEX_SHADER_HPP

#include <vector>

#include "Enum.hpp"
#include "common/VecFwd.hpp"

#include "VertexAttributeBuffer.hpp"

namespace my_gl {

     struct MatrixParam;
     struct GroupLightingParam;

     using std::vector;

     class VertexShader {
	  public:

	       VertexShader(const MatrixParam& matrixParam,
			 const GroupLightingParam& groupLightingParam);

	       void setNormalizedNormal(bool normalizedNormal);

	       virtual ~VertexShader ();

	       virtual void shade(const Vec4* inputAttributes,
			 AttributeGroupRef outputAttributes);

	       void enable(NormalizeNormal normalizeNormal);

	  protected:

	       /** 
		* @brief emulate GLSL  ftransform()
		* 
		* @param inVertex
		* 
		* @return 
		*/
	       Vec4 ftransform(const Vec4& inVertex);

	       /** 
		* @brief process normal with _normalizeNormal 
		* parameter 
		* 
		* @param inNormal
		* 
		* @return 
		*/
	       Vec3 fnormal(const Vec3& inNormal);

	       virtual void shade(

			 const Vec4& inVertex,
			 const Vec4& inColor,
			 const Vec4& inNormal,
			 const Vec4& inTexCoord,

			 Vec4& outPosition,
			 Vec4& outPointSize,
			 Vec4& outFrontColor,
			 Vec4& outBackColor,
			 Vec4& outTexCoord
			 )=0;

	  protected:
	       const MatrixParam& _matrixParam;
	       const GroupLightingParam& _groupLightingParam;

	  private:

	       bool _normalizeNormal;
	       bool _rescaleNormal;

     };

} /* my_gl */



#endif /* end of include guard: VERTEX_SHADER_HPP */
