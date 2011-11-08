/*
 * =====================================================================================
 *
 *       Filename:  ObjectNameManager.hpp
 *
 *    Description:  to manage object name glGenBuffers/glGenTextures
 *
 *        Version:  1.0
 *        Created:  2011-9-14 17:43:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OBJECT_NAME_MANAGER_HPP

#define OBJECT_NAME_MANAGER_HPP

#include <cstddef>

#include <boost/icl/interval_set.hpp>

#include "Typedef.hpp"

namespace my_gl {

     using boost::icl::interval_set;

     class ObjectNameManager {
     public:

	  ObjectNameManager();

	  void generateNames(size_t size,Name* names);
     
	  void recycleName(Name name);

     private:

	  interval_set<Name> _usedNames;

     };
	
} /* my_gl */


#endif /* end of include guard: OBJECT_NAME_MANAGER_HPP */
