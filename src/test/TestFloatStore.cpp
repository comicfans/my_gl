/*
 * =====================================================================================
 *
 *       Filename:  TestFloatStore.cpp
 *
 *    Description:  float data store format test
 *    		    IEEE float  binary  reinterpret_cast to int
 *    		    will lead to same more/less relationship
 *
 *
 *        Version:  1.0
 *        Created:  2012-1-15 22:42:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <cstdint>
#include <cassert>

using std::rand;

int main(int argc, const char *argv[])
{

     for (int i=0; i<10000; ++i)
     {
	  std::srand(i);

	  uint32_t r1=rand(),
		   r2=rand();

	  float f1=*(reinterpret_cast<float*>(&r1)),
		f2=*(reinterpret_cast<float*>(&r2));

	  assert(((r1>r2)==(f1>f2))||"float revert");

     }
	
}
