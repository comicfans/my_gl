/*
 * =====================================================================================
 *
 *       Filename:  VectorSizeTest.cpp
 *
 *    Description:  test sizeof Vector
 *
 *        Version:  1.0
 *        Created:  2011-9-28 9:57:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>

#include "common/Vector.hpp"


using std::cout;
using std::endl;

using my_gl::Vector;

class VectorClass
{
	       float _values[4];
 

};

int main(int argc, const char *argv[])
{
	
     cout<<sizeof(Vector)<<" "<<sizeof(VectorClass)<<endl;
}
