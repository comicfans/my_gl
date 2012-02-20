/*
 * =====================================================================================
 *
 *       Filename:  TextureObject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-4 18:18:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TextureObject.hpp"

#include <cmath>

#include <boost/assign/list_of.hpp>

#include "common/UntypedArray.hpp"
#include "common/PointerFunction.hpp"
#include "pipeline/interpolator/Interpolator.hpp"

namespace my_gl {

     using std::min;
     using std::max;
     using std::fmod;
     using std::abs;
     using std::bind;
     using std::placeholders::_1;
     using std::placeholders::_2;

	 int nearbyint(double value){return value;}

     float clamp(float value,float total)
     {
	  return value>0?
	       min<float>(value,total):
	       max<float>(value,0.0);
     }

     float repeat(float value,float total)
     {
	  return value>0?
	       fmod(value,total):
	       total+fmod(value,total);
     }

     float mirrorRepeat(float value,float total)
     {
	  float mirrorPart=fmod(abs(value),total*2);

	  return value>total?total-mirrorPart:
	       mirrorPart;
     }

     static unordered_map<GLenum,TextureObject::Wrapper>
	  WRAPPERS=boost::assign::map_list_of
	  (GL_CLAMP,clamp)(GL_REPEAT,repeat)(GL_MIRRORED_REPEAT,mirrorRepeat);

     TextureObject::TextureObject(Name name)
	  :PixelObject(name)
     {
	  texParameter(GL_TEXTURE_WRAP_S,
		    GL_REPEAT);
	  texParameter(GL_TEXTURE_WRAP_T,
		    GL_REPEAT);

	  ALL_FILTERS[GL_LINEAR]=
	       bind(&TextureObject::linear,this,_1,_2);

	  ALL_FILTERS[GL_NEAREST]=
	       bind(&TextureObject::nearest,this,_1,_2);


	  texParameter(GL_TEXTURE_MAG_FILTER,
		    GL_LINEAR);

	  texParameter(GL_TEXTURE_MIN_FILTER,
		    GL_LINEAR);

     }
	
     void TextureObject::texParameter
	  (GLenum pname,GLenum value)
     {
	  if(pname==GL_TEXTURE_WRAP_S || pname==GL_TEXTURE_WRAP_T)
	  {
	       _stWrapMode[pname]=value;
	       _stWrapper[pname]=WRAPPERS[value];
	  }
	  else
	  {
	       _magMinFilter[pname]=ALL_FILTERS[value];
	  }
     }

     Vec4 TextureObject::operator()(float s,float t)const
	{
	     //HALF_PIXEL adjust, makes 
	     //wrapper treat coord zero-based
	     auto sWrapperIt=_stWrapper.find(GL_TEXTURE_WRAP_S);

	     assert(sWrapperIt!=_stWrapper.end());

	     float u=(sWrapperIt->second)(s*width()-HALF_PIXEL,width()-HALF_PIXEL);

	     auto tWrapperIt=_stWrapper.find(GL_TEXTURE_WRAP_T);

	     float v=(tWrapperIt->second)(t*height()-HALF_PIXEL,height()-HALF_PIXEL);

	     //TODO currently use MAG_FILTER as filter
//#warning right here?
	     auto it=ALL_FILTERS.find(GL_TEXTURE_MAG_FILTER);
	     assert(it!=ALL_FILTERS.end());
	     return (it->second)(u,v);
	}


	Vec4 TextureObject::getVec
	     (size_t u,size_t v)const
	{
	     int offset=(v*width()+u)*
		  Vec4::LENGTH;

	     return getBufferPointer<float>()+offset;
	}


	Vec4 TextureObject::nearest(float u,float v)const
	{
	     //TODO 
	     //s [0,1] -> wrap(s*width()-0.5) [0,width()-0.5] ??
	     assert(u>=0 && nearbyint(u)< width()-0.5);
	     assert(v>=0 && nearbyint(v)< height()-0.5 );

	     return getVec(nearbyint(u),
		       nearbyint(v));

	}

	Vec4 TextureObject::linear(float u,float v)const
	{

	     //TODO 
	     //s [0,1] -> wrap(s*width()-0.5) [0,width()-0.5] ??
	     assert(u>=0 && nearbyint(u)< width()-0.5);
	     assert(v>=0 && nearbyint(v)< height()-0.5 );

	     size_t leftLowerU=floor(u),
		    leftLowerV=floor(v),
		    rightUpperU=ceil(u),
		    rightUpperV=ceil(v);

	     float uDirectionPercent=u-leftLowerU,
		   vDirectionPercent=v-leftLowerV;

	     Vec4 upper,lower;

	     Interpolator::calculate(
		       getVec(leftLowerU,leftLowerV),
		       getVec(rightUpperU,leftLowerV),
		       uDirectionPercent,lower);

	     Interpolator::calculate(
		       getVec(leftLowerU,rightUpperV),
		       getVec(rightUpperU,rightUpperV),
		       uDirectionPercent,upper);

	     Vec4 ret;

	     Interpolator::calculate(lower,upper,
		       vDirectionPercent,ret);

	     return ret;

	}

} /* my_gl */
