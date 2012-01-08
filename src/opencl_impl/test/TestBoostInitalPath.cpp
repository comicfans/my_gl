/*
 * =====================================================================================
 *
 *       Filename:  TestBoostInitalPath.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-8 12:24:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <boost/filesystem.hpp>

#include <iostream>
int main(int argc, const char *argv[])
{

     std::cout<<boost::filesystem::initial_path();
	
	return 0;
}
