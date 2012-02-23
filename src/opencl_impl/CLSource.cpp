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

#include <memory>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/foreach.hpp>
#include <boost/assert.hpp>

using boost::filesystem::ifstream;
using std::unique_ptr;

namespace my_gl {

     CLSource::CLSource(const std::string& filename)
     {
	  auto cwd=boost::filesystem::current_path();

	  auto fullName=cwd/filename;

	  ifstream clFile(fullName,ifstream::in|ifstream::binary);


	  BOOST_ASSERT_MSG(boost::filesystem::exists(fullName),"file not exists");

	  BOOST_ASSERT_MSG(clFile ,"file open failed");

	  clFile.seekg(0,ifstream::end);

	  int fileSize=clFile.tellg();

	  clFile.seekg(0,ifstream::beg);

	  unique_ptr<char[]> tempBuff(new char[fileSize+1]);

	  clFile.read(tempBuff.get(),fileSize);

	  tempBuff[fileSize]='\0';

	  _rawStrings.push_back(std::string(tempBuff.get()));

	  _clSources.push_back(std::make_pair(_rawStrings.back().c_str(),_rawStrings.back().length()));



     }
	
	
     const cl::Program::Sources CLSource::getSources()const
     {
	  return _clSources;
     }
} /* my_gl */
