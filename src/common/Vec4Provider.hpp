#ifndef VEC4_PROVIDER_HPP

#define VEC4_PROVIDER_HPP

#include "Vec.hpp"

namespace my_gl {
     class Vec4Provider {
     public:
     	virtual Vec4 getValue(size_t index)=0;
	virtual ~Vec4Provider();
     };
	
} /* my_gl */


#endif /* end of include guard: VEC4_PROVIDER_HPP */
