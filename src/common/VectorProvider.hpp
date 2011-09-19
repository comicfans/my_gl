#ifndef VECTOR_PROVIDER_HPP

#define VECTOR_PROVIDER_HPP

#include "Vector.hpp"

namespace my_gl {
     class VectorProvider {
     public:
     	virtual Vector value()=0;
     };
	
} /* my_gl */


#endif /* end of include guard: VECTOR_PROVIDER_HPP */
