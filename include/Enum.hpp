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

#define GL_RGB 0x1907
#define GL_RGBA 0x1908
    
     enum ImageFormat{RGB,RGBA};

#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_BYTE                  0x1401



#define GL_BYTE                           0x1400
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_FLOAT                          0x1406
#define GL_FIXED                          0x140C


    
     /** 
      * @brief glBindBuffer
      */
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
     enum BufferTarget{ARRAY_BUFFER,ELEMENT_ARRAY_BUFFER};

     //TODO
     enum BindState{VERTEX,COLOR,NORMAL,TEXCOORD,ELEMENTS};


#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8
     enum DataUsage{STATIC_DRAW,DYNAMIC_DRAW};

     /** 
      * @brief glMatrixMode()
      */
#define GL_MODELVIEW 0x1700
#define GL_PROJECTION 0x1701
#define GL_TEXTURE 0x1702
     enum MatrixMode{MODEL_VIEW,PROJECTION,TEXTURE};


     /** 
      * @brief glDrawArray/glDrawElements
      */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
     enum PrimitiveMode{POINTS,LINES,TRIANGLES,LINE_STRIP,LINE_LOOP,
	  TRIANGLE_STRIP,TRIANGLE_FAN};

     /** 
      * @brief glDepthFunc
      */
#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207
     enum DepthFunc{NEVER,ALWAYS,LESS,LEQUAL,
	  EQUAL,GREATER,GEQUAL,NOTEQUAL};

#define GL_LIGHT0 0x4000
#define GL_LIGHT1 0x4001
#define GL_LIGHT2 0x4002
#define GL_LIGHT3 0x4003
#define GL_LIGHT4 0x4004
#define GL_LIGHT5 0x4005
#define GL_LIGHT6 0x4006
#define GL_LIGHT7 0x4007
     enum LightIndex{LIGHT0,LIGHT1,LIGHT2,
	  LIGHT3,LIGHT4,LIGHT5,LIGHT6,LIGHT7};

#define GL_AMBIENT 0x1200
#define GL_DIFFUSE 0x1201
#define GL_SPECULAR 0x1202
#define GL_POSITION 0x1203
#define GL_SPOT_DIRECTION 0x1204
#define GL_SPOT_EXPONENT 0x1205
#define GL_SPOT_CUTOFF 0x1206
#define GL_CONSTANT_ATTENUATION 0x1207
#define GL_LINEAR_ATTENUATION 0x1208
#define GL_QUADRATIC_ATTENUATION 0x1209

     enum LightParamName{
	  AMBIENT,DIFFUSE,SPECULAR,LINEAR_ATTENUATION,QUADRATIC_ATTENUATION,SPOT_CUTOFF,CONSTANT_ATTENUATION,
	  SPOT_DIRECTION,SPOT_EXPONENT,POSITION,

	       //TODO
	  AMBIENT_AND_DIFFUSE,SHININESS,EMISSION, TWO_SIDE};

#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408
     enum Face{FRONT,BACK,FRONT_AND_BACK};

#define GL_CW                             0x0900
#define GL_CCW                            0x0901
     enum FaceMode{CW=0,CCW=1};


     //TODO
     enum NormalizeNormal{RESCALE_NORMAL,NORMALIZE};

     //in opengl es 1.0, only TEXTURE_2D is supported
#define GL_TEXTURE_2D 0x0DE1
     enum TexTarget{TEXTURE_2D};

#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
     enum TexFilterMode{NEAREST,LINEAR};

#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
     enum TexWrapName{TEXTURE_WRAP_S,TEXTURE_WRAP_T};

#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801

     enum	TexFilterName{TEXTURE_MAG_FILTER,TEXTURE_MIN_FILTER};

#define GL_CLAMP 0x2900
#define GL_REPEAT 0x2901
#define GL_MIRRORED_REPEAT                0x8370
     enum TexWrapMode{CLAMP,REPEAT,MIRRORED_REPEAT};

#define GL_MODULATE 0x2100
#define GL_DECAL 0x2101
#define GL_REPLACE 0x1E01
     enum TexEnvMode{REPLACE,MODULATE,DECAL};
} /* my_gl */



#endif /* end of include guard: ENUM_HPP */
