/*
 * =====================================================================================
 *
 *       Filename:  Image.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 12:17:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef IMAGE_HPP

#define IMAGE_HPP

#include <cstdint>
#include <memory>

namespace my_gl {
     struct RGBARef
     {
	  private:
	  uint8_t *_bytes;

	  public:
	  RGBARef(uint8_t *bytes);

	  uint8_t& R;
	  uint8_t& G;
	  uint8_t& B;
	  uint8_t& A;

     };

     struct Image
     {

	  Image(int width,int height);

	  const int width;
	  const int height;

	  RGBARef operator()(int yIdx,int xIdx);

	       
	  int byteSize()const;

	  uint8_t * rawData();

	  private:
	  std::unique_ptr<uint8_t[]> _imageBytesPtr;
     };


} /* my_gl */


#endif /* end of include guard: IMAGE_HPP */


