/*
 * =====================================================================================
 *
 *       Filename:  ObjectNameManager.cpp
 *
 *    Description:  implementation of ObjectNameManager
 *
 *        Version:  1.0
 *        Created:  2011-9-14 18:29:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ObjectNameManager.hpp"

#include <algorithm>
#include <boost/icl/right_open_interval.hpp>

namespace my_gl{
     using std::generate_n;

     using boost::icl::right_open_interval;
     using boost::icl::interval;

     typedef interval<Name>::type Interval;
     ObjectNameManager::ObjectNameManager()
     {
	  _usedNames.add(Interval(0,1));
     }

     void ObjectNameManager::generateNames(size_t size,  Name *names)
     {
	  //get last segment Interval 
	  auto end=_usedNames.end();

	  auto lastSegPos=--end;

	  Name beginName=lastSegPos->upper();

	  _usedNames.add(Interval(beginName,beginName+size));

	  for (size_t i=0; i<size; ++i)
	  {
	       *(names+i)=beginName+i;
	  }
     }

     void ObjectNameManager::recycleNames(size_t size, Name *names)
     {
	  for (size_t i=0; i<size; ++i)
	  {
	       Name thisName=*(names+i);
	       assert(contains(_usedNames,thisName));
	       assert(thisName>0);
	       _usedNames.erase(thisName);
	  }
     }
	
} /* my_gl */
