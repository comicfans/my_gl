/*
 * =====================================================================================
 *
 *       Filename:  UniqueNormalProvider.hpp
 *
 *    Description:  hold a unique normal
 *
 *        Version:  1.0
 *        Created:  2011-9-14 16:22:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef UNIQUE_NORMAL_PROVIDER_HPP

#define UNIQUE_NORMAL_PROVIDER_HPP

#include "common/Vector.hpp"
#include "NormalProvider.hpp"

namespace my_gl {
	class UniqueNormalProvider:public NormalProvider {
	public:
	     virtual Vector get() noexcept;

	     void set(Vector normal) noexcept;
	private:
	     Vector _normal;
	};
} /* my_gl */

#endif /* end of include guard: UNIQUE_NORMAL_PROVIDER_HPP */
