#ifndef VEC4_PROVIDER_HPP

#define VEC4_PROVIDER_HPP

#include "Vec4.hpp"

namespace my_gl {
     class Vec4Provider {
     public:
     	virtual Vec4 value()=0;
	virtual void next(size_t steps=1)=0;
	virtual ~Vec4Provider();
     };
	
} /* my_gl */


#endif /* end of include guard: VEC4_PROVIDER_HPP */
