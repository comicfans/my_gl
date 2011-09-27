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
    
     enum class BufferTarget{ARRAY_BUFFER,ELEMENT_ARRAY_BUFFER};

     enum class BindState{VERTEX,NORMAL,COLOR,TEXCOORD,ELEMENTS};

     enum class DataUsage{STATIC_DRAW,DYNAMIC_DRAW};

     /** 
      * @brief glMatrixMode()
      */
     enum class MatrixMode{MODEL_VIEW,PROJECTION,TEXTURE};

     enum class PrimitiveMode{POINTS,LINE_STRIP,LINE_LOOP,LINES,
	  TRIANGLE_STRIP,TRIANGLE_FAN,TRIANGLES};
} /* my_gl */



#endif /* end of include guard: ENUM_HPP */
