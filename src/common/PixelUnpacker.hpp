/*
 * =====================================================================================
 *
 *       Filename:  PixelUnpacker.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-18 10:30:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PIXEL_UNPACKER_HPP

#define PIXEL_UNPACKER_HPP

#include <cstdint>
#include <cstddef>
#include <functional>

#include "Enum.hpp"

namespace my_gl {

     using std::function;
     class PixelUnpacker {
     public:
     	PixelUnpacker (const void * source,float* dest,
		  size_t width,size_t height,
		  ImageFormat format,StoreType type,
		  size_t jumpBlocks=0);

	void unpack();
     private:

	const size_t _blockSize;

	const int8_t *_currentSource;
	float * _currentDest;
	const void * const _sourceEnd;

	function<void(const void* ,float* )> _unpacker;

     };
	
} /* my_gl */

#endif /* end of include guard: PIXEL_UNPACKER_HPP */
