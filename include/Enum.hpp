/*
 * =====================================================================================
 *
 *       Filename:  Enum.hpp
 *
 *    Description:  all enum of GL call
 *
 *        Version:  1.0
 *        Created:  2011-9-13 21:13:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ENUM_HPP

#define ENUM_HPP

namespace my_gl {
	
	
     enum class ImageFormat{RGB,RGBA};

     enum class StoreType{UNSIGNED_BYTE,UNSIGNED_SHORT_5_6_5,
	       UNSIGNED_SHORT_4_4_4_4,UNSIGNED_SHORT_5_5_5_1};

     enum class DataType{BYTE,UNSIGNED_BYTE,
	  SHORT,UNSIGNED_SHORT,FIXED,FLOAT};
    
     /** 
      * @brief glBindBuffer
      */
     enum class BufferTarget{ARRAY_BUFFER,ELEMENT_ARRAY_BUFFER};

     enum class BindState{VERTEX,COLOR,NORMAL,TEXCOORD,ELEMENTS};

     enum class DataUsage{STATIC_DRAW,DYNAMIC_DRAW};

     /** 
      * @brief glMatrixMode()
      */
     enum class MatrixMode{MODEL_VIEW,PROJECTION,TEXTURE};


     /** 
      * @brief glDrawArray/glDrawElements
      */
     enum class PrimitiveMode{POINTS,LINES,TRIANGLES,LINE_STRIP,LINE_LOOP,
	  TRIANGLE_STRIP,TRIANGLE_FAN};

     /** 
      * @brief glDepthFunc
      */
     enum class DepthFunc{NEVER,ALWAYS,LESS,LEQUAL,
	  EQUAL,GREATER,GEQUAL,NOTEQUAL};

     enum class LightIndex{LIGHT0,LIGHT1,LIGHT2,
	  LIGHT3,LIGHT4,LIGHT5,LIGHT6,LIGHT7,LIGHTING};

     enum class LightParamName{AMBIENT,DIFFUSE,
	  AMBIENT_AND_DIFFUSE,SPECULAR,SHININESS,
	  EMISSION,POSITION,SPOT_DIRECTION,SPOT_EXPONENT,
	  SPOT_CUTOFF,CONSTANT_ATTENUATION,
	  LINEAR_ATTENUATION,QUADRATIC_ATTENUATION,TWO_SIDE};

     enum class Face{FRONT,BACK,FRONT_AND_BACK};

     enum class NormalizeNormal{RESCALE_NORMAL,NORMALIZE};

     enum class TexFilterMode{NEAREST,LINEAR};

     enum class TexWrapName{TEXTURE_WRAP_S,TEXTURE_WRAP_T};

     enum class	TexFilterName{TEXTURE_MAG_FILTER,TEXTURE_MIN_FILTER};

     enum class TexWrapMode{CLAMP,REPEAT,MIRRORED_REPEAT};
} /* my_gl */



#endif /* end of include guard: ENUM_HPP */
