/*
 * =====================================================================================
 *
 *       Filename:  CLSource.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-8 12:13:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "CLSource.hpp"

#include <cassert>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using boost::filesystem::ifstream;

namespace my_gl {

     CLSource::CLSource(const std::string& filename)
     {
	  auto cwd=boost::filesystem::current_path();

	  auto fullName=cwd/filename;

	  ifstream clFile(fullName);

	  assert(boost::filesystem::exists(fullName) || "file not exists");

	  assert(clFile || "no opencl file loaded");

	  std::string oneLine;

	  while (!clFile.eof())
	  {
	       std::getline(clFile,oneLine);

	       _rawStrings.push_back(oneLine);

	       _clSources.push_back
		    (std::make_pair(oneLine.c_str(),oneLine.length()));
	  }


     }
	
	
     const cl::Program::Sources CLSource::getSources()const
     {
	  return _clSources;
     }
} /* my_gl */
