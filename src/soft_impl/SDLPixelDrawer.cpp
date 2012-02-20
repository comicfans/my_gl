/*
 * =====================================================================================
 *
 *       Filename:  SDLPixelDrawer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-26 9:39:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SDLPixelDrawer.hpp"

#include <cassert>
#include <SDL.h>

#include "pipeline/ColorBuffer.hpp"
#include "pipeline/rasterizer/WinCoord.hpp"
namespace my_gl {

     SDLPixelDrawer::~SDLPixelDrawer()
     {
	  SDL_Quit();
     }


	  void setPixelBpp8(Uint8 *finalPixel,Uint32 toSet)
	  {
	       *finalPixel=toSet;
	  }
  
	  void setPixelBpp16(Uint8 *finalPixel,Uint32 toSet)
	  {
	       *(Uint16*)finalPixel = toSet;
	  }
     
	  void setPixelBpp32(Uint8 *finalPixel,Uint32 toSet)
	  {
	       *(Uint32*)finalPixel = toSet;
	  }

  
	  template<bool littleEndia>
	  void setPixelBpp24(Uint8 *finalPixel,Uint32 toSet);

	  template<>
	  void setPixelBpp24<true>(Uint8 *finalPixel,Uint32 toSet)
	  {
	       finalPixel[0] = toSet & 0xff;
	       finalPixel[1] = (toSet>> 8) & 0xff;
	       finalPixel[2] = (toSet>> 16) & 0xff;
	  }

     template<>
	  void setPixelBpp24<false>(Uint8 *finalPixel,Uint32 toSet)
	  {
	       finalPixel[0] = (toSet>> 16) & 0xff;
	       finalPixel[1] = (toSet>> 8) & 0xff;
	       finalPixel[2] = toSet& 0xff;
	  }


     void SDLPixelDrawer::onInit(size_t width,size_t height)
     {
	  //init sdl
	  SDL_Init(SDL_INIT_VIDEO);

	  _width=width;
	  _height=height;

	  _screenPtr= 
	       SDL_SetVideoMode(width, height, 0, SDL_SWSURFACE);

	  //TODO no check currently
	  assert(_screenPtr);

	  switch (_screenPtr->format->BytesPerPixel)
	  {
	       case 1:
		    {
			 _setPixelFunc=setPixelBpp8;
			 break;
		    }
	       case 2:
		    {
			 _setPixelFunc=setPixelBpp16;
			 break;
		    }
	       case 3:
		    {
			 _setPixelFunc=setPixelBpp24<SDL_BYTEORDER==SDL_LIL_ENDIAN>;
			 break;
		    }
	       case 4:
		    {
			 _setPixelFunc=setPixelBpp32;
			 break;
		    }
	       default:
		    {
			 assert(false || "bpp not support");
		    }
	  }
     }

     SDLPixelDrawer::SurfaceLocker::SurfaceLocker(SDL_Surface * toLock)
	  {
	       _toLock=toLock;
	       if (SDL_MUSTLOCK(_toLock))
	       {
		    SDL_LockSurface(_toLock);
	       }
	  }

     SDLPixelDrawer::SurfaceLocker::~SurfaceLocker()
	  {     if (SDL_MUSTLOCK(_toLock))
	       {
		    SDL_UnlockSurface(_toLock);
	       }
	  }


     void SDLPixelDrawer::dropEvent()
     {
	  SDL_Event event;
	  //use sdl as final output 
	  //but sdl poll event from system
	  //drop all these event 
	  //if not ,window will be locked
	  while(SDL_PollEvent(&event));
     }

     static inline Uint8 toUint8(float value)
     {
	  assert(value>=0 && value<=1);
	  return 255*value;
     }

     void SDLPixelDrawer::onFlush()
     {
	  SDL_Flip(_screenPtr);

     }

     void SDLPixelDrawer::onDraw(const ColorBuffer& frameBuffer)
     {
	  SurfaceLocker locker(_screenPtr);

	  for (size_t y=0; y<_height; ++y)
	  {
	       for (size_t x=0; x<_width; ++x)
	       {
		    const Vec4& color=frameBuffer(
			      WinCoord(x,y));

		    Uint32 packedValue=
			 SDL_MapRGB(_screenPtr->format,
				   toUint8(color[0]),toUint8(color[1]),toUint8(color[2]));

	  //SDL surface origin is left-upper
	  //but opengl default frameBuffer origin is left-lower

		    Uint8 *p = (Uint8 *)_screenPtr ->pixels + 
			 (_height-y) * _screenPtr->pitch + 
			 x * _screenPtr->format->BytesPerPixel;

		    _setPixelFunc(p,packedValue);

	       }
	  }

	  dropEvent();

     }


	  
     size_t SDLPixelDrawer::width()const{return _width;}

     size_t SDLPixelDrawer::height()const {return _height;}
} /* my_gl */
