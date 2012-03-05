/*
 * =====================================================================================
 *
 *       Filename:  PixelUnpacker.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-18 10:31:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "PixelUnpacker.hpp"

#include <cassert>

namespace my_gl {

	
     static size_t calcBlockSize(GLenum format,  
	       GLenum type)
     {
	  if (type==GL_UNSIGNED_BYTE)
	  {
	       //RGB,RGBA + UNSIGNED_BYTE
	       return format==GL_RGB?3:4;
	  }
	  else
	  {
	       //RGB,RGBA + UNSIGNED_SHORT_5_6_5,UNSIGNED_SHORT_4_4_4_4,
	       //UNSIGNED_SHORT_5_5_5_1
	       return 2;
	  }
     }

     static void RGBUnpack(const void *source,float *dest)
     {
	  const uint8_t *pUbyte=static_cast<const uint8_t*>(source);

	  const int fullRange=255;
	  for(int i=0;i<3;++i)
	  {
	       dest[i]=pUbyte[i]/fullRange;
	  }
     }

	  //A not exist ,expand to 1.0 default
	  //see GL spec Final Expansion to RGBA
     const float DEFAULT_ALPHA=1.0;

     static void RGBAUnpack(const void *source,float *dest)
     {
	  RGBUnpack(source,dest);
	  dest[3]=DEFAULT_ALPHA;
     }

     /** 
      * @brief extract bit from beginBit with bit number=size
      * 
      * @param source
      * @param beginBit
      * @param size
      * 
      * @return 
      */
     static uint32_t extract(const void* source,int beginBit,int size)
     {
	  uint32_t ret= static_cast
	       <const uint32_t*>(source)[0];

	  ret<<=beginBit;
	  ret>>=(32-size);
	  return ret;
     }

     static void Packed565Unpack(const void *source,float *dest)
     {
	  dest[0]=extract(source,0,5)/32.0;
	  dest[1]=extract(source,5,6)/64.0;
	  dest[2]=extract(source,11,5)/32.0;
	  dest[3]=DEFAULT_ALPHA;
     }

     static void Packed4444Unpack(const void *source,float *dest)
     {
	  for(int i=0;i<4;++i)
	  {dest[i]=extract(source,i*4,4)/16.0;}
     }

     static void Packed5551Unpack(const void *source,float *dest)
     {
	  for(int i=0;i<3;++i)
	  { dest[i]=extract(source,i*5,5)/32.0;  }
	  dest[3]=extract(source,15,1);
     }

     PixelUnpacker::PixelUnpacker (const void * source,
	       float* dest,size_t width,size_t height,
	       GLenum format,GLenum type,
	       size_t jumpBlocks)
	  :_blockSize(calcBlockSize(format,type)),
	  _currentSource(static_cast<const int8_t*>(source)
		    +_blockSize*jumpBlocks),
	  _currentDest(dest+4*sizeof(float)*jumpBlocks),
	  _sourceEnd(_currentSource+(jumpBlocks+width*height)*_blockSize)
	   
     {
	  if (type==GL_UNSIGNED_BYTE)
	  {
	       assert(format==GL_RGB || format==GL_RGBA);
	       _unpacker=(format==GL_RGB?RGBUnpack:RGBAUnpack);
	  }
	  else
	  {
	       switch (type)
	       {
		    case GL_UNSIGNED_SHORT_5_6_5:
			 {_unpacker=Packed565Unpack;break;}
		    case GL_UNSIGNED_SHORT_4_4_4_4:
			 {_unpacker=Packed4444Unpack;break;}
		    case GL_UNSIGNED_SHORT_5_5_5_1:
			 {_unpacker=Packed5551Unpack;break;}
		    default:
			 {assert(false);}
	       }
	  }
     }

     void PixelUnpacker::unpack()
     {
	  while (_currentSource<_sourceEnd)
	  {
	       _unpacker(_currentSource,_currentDest);

	       _currentSource+=_blockSize;
	       _currentDest+=4;
	  }
     }

} /* my_gl */
