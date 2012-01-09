/*
 * =====================================================================================
 *
 *       Filename:  CLSource.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-8 11:31:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CL_SOURCE_HPP

#define CL_SOURCE_HPP

#include <string>
#include <vector>
#include <CL/cl.hpp>

namespace my_gl {

     class CLSource {
     public:
     	CLSource (const std::string& filename);

	const cl::Program::Sources getSources()const;
     
     private:

	std::vector<std::string> _rawStrings;
	cl::Program::Sources _clSources;
     };
	
} /* my_gl */


#endif /* end of include guard: CL_SOURCE_HPP */
