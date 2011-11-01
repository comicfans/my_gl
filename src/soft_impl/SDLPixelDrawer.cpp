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

#include <SDL.h>

#include "pipeline/ColorBuffer.hpp"
#include "pipeline/rasterizer/WinCoord.hpp"
namespace my_gl {

     SDLPixelDrawer::~SDLPixelDrawer()
     {
	  SDL_Quit();
     }

     void SDLPixelDrawer::onInit(size_t width,size_t height)
     {
	  //init sdl
	  SDL_Init(SDL_INIT_VIDEO);

	  _width=width;
	  _height=height;

	  _screenPtr= 
	       SDL_SetVideoMode(width, height, 8, SDL_SWSURFACE);
     }

     struct SurfaceLocker
     {
	  SurfaceLocker(SDL_Surface * toLock)
	  {
	       _toLock=toLock;
	       if (SDL_MUSTLOCK(_toLock))
	       {
		    SDL_LockSurface(_toLock);
	       }
	  }
	  ~SurfaceLocker()
	  {     if (SDL_MUSTLOCK(_toLock))
	       {
		    SDL_UnlockSurface(_toLock);
	       }
	  }
	  private:
	  SDL_Surface *_toLock;

     };

     static void dropEvent()
     {
	  SDL_Event event;
	  while(SDL_PollEvent(&event));
     }

     /*
      * came from SDL guide
      * Set the pixel at (x, y) to the given value
      * NOTE: The surface must be locked before calling this!
      */
     void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
     {
	  int bpp = surface->format->BytesPerPixel;
	  /* Here p is the address to the pixel we want to set */
	  Uint8 *p = (Uint8 *)surface->pixels + 
	       y * surface->pitch + x * bpp;

	  switch(bpp) {
	       case 1:
		    *p = pixel;
		    break;

	       case 2:
		    *(Uint16 *)p = pixel;
		    break;

	       case 3:
		    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			 p[0] = (pixel >> 16) & 0xff;
			 p[1] = (pixel >> 8) & 0xff;
			 p[2] = pixel & 0xff;
		    } else {
			 p[0] = pixel & 0xff;
			 p[1] = (pixel >> 8) & 0xff;
			 p[2] = (pixel >> 16) & 0xff;
		    }
		    break;

	       case 4:
		    *(Uint32 *)p = pixel;
		    break;
	  }
     }

     static inline Uint8 toUint8(float value)
     {
	  return 255*value;
     }

     void SDLPixelDrawer::onFlush()
     {
	  SDL_Flip(_screenPtr);

     }

     void SDLPixelDrawer::onDraw(const ColorBuffer& frameBuffer)
     {
	  SurfaceLocker locker(_screenPtr);

	  //SDL surface origin is left-upper
	  //but opengl default frameBuffer origin is left-lower

	  for (size_t y=0; y<_height; ++y)
	  {
	       for (size_t x=0; x<_width; ++x)
	       {
		    const Vec4& color=frameBuffer(
			      WinCoord(x,y));

		    Uint32 packedValue=
			 SDL_MapRGB(_screenPtr->format,
				   toUint8(color[0]),toUint8(color[1]),toUint8(color[2]));
		    putPixel(_screenPtr,x,_height-y,packedValue);
	       }
	  }

	  dropEvent();

     }

} /* my_gl */
