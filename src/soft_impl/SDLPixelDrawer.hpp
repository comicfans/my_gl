/*
 * =====================================================================================
 *
 *       Filename:  SDLPixelDrawer.hpp
 *
 *    Description:  use sdl to draw pixels
 *
 *        Version:  1.0
 *        Created:  2011-10-26 9:35:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SDL_PIXEL_DRAWER_HPP

#define SDL_PIXEL_DRAWER_HPP

#include <memory>
#include <functional>
#include <cstdint>

#include "PixelDrawer.hpp"

struct SDL_Surface;

namespace my_gl {

     class ColorBuffer;
     class SDLPixelDrawer :public PixelDrawer
     {
     public:
	  
	  virtual void onInit(size_t width,size_t height);

	  virtual void onDraw(const ColorBuffer& frameBuffer);

	  virtual void onFlush();
     	
	  virtual ~SDLPixelDrawer  ();

	  size_t width()const ;

	  size_t height()const ;

     protected:

	SDL_Surface *_screenPtr;
     
	void dropEvent();

	std::function<void(uint8_t*,uint32_t)> _setPixelFunc;

     /** 
      * @brief implement SDL_Surface lock RAII idiom
      */
	struct SurfaceLocker
	{

	     SurfaceLocker(SDL_Surface * toLock);
	     ~SurfaceLocker();
	     private:
	     SDL_Surface *_toLock;
	};

	

     private:

	size_t _width;
	size_t _height;


     };
	
} /* my_gl */


#endif /* end of include guard: SDL_PIXEL_DRAWER_HPP */
