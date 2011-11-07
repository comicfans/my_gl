/*
 * =====================================================================================
 *
 *       Filename:  TextureObject.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-4 15:22:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEXTURE_OBJECT_HPP

#define TEXTURE_OBJECT_HPP

#include <functional>

#include "PixelObject.hpp"
#include "common/Vec.hpp"


namespace my_gl {

     using std::function;

     class TextureObject :public PixelObject{
     public:

     	TextureObject (Name name);

	Vec4 operator()(float s,float t)const;

	void texParameter
	     (TexWrapName warpName,TexWrapMode warpMode);


	/** 
	 * @brief set filter mode
	 * in fixed functional pipeline
	 * texture is applied in rasterize stage
	 * texture image will be scaled to 
	 * framebuffer image, as I read 
	 * MAG_FILTER and MIN_FILTER is applied
	 * here. but in GLSL ,sampler is used 
	 * in fragment shader to obtain texture
	 * image,at this time,rasterize is already
	 * applied, so there is *NO* MAG_FILTER or
	 * MIN_FILTER, but when sampling, a filter
	 * type should be used ,it can be NEAREST
	 * or LINEAR
	 * 
	 * @param filterName
	 * @param filterMode
	 * 
	 * @return 
	 */
	void texParameter
	     (TexFilterName filterName,TexFilterMode filterMode);

	typedef function<float(float,size_t)> Wrapper;

     private:


	typedef function<Vec4(float ,float )> Filter;

	TexWrapMode _stWrapMode[2];

	Wrapper _stWrapper[2];

	TexFilterMode _magMinFilterMode[2];

	Filter _magMinFilter[2];

	Filter ALL_FILTERS[2];

	Vec4 nearest(float u,float v)const;

	Vec4 linear(float u,float v)const;

	Vec4 getVec(size_t u,size_t v)const;

     };
	
} /* my_gl */


#endif /* end of include guard: TEXTURE_OBJECT_HPP */
