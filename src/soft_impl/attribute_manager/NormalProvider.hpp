/*
 * =====================================================================================
 *
 *       Filename:  NormalProvider.hpp
 *
 *    Description:  interface to provide a normal
 *
 *        Version:  1.0
 *        Created:  2011-9-14 13:52:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef NORMAL_PROVIDER_HPP

#define NORMAL_PROVIDER_HPP

namespace my_gl {
	class NormalProvider {
	public:
	     virtual Vector get() noexcept=0;
	};
} /* my_gl */

#endif /* end of include guard: NORMAL_PROVIDER_HPP */
