/*
 * =====================================================================================
 *
 *       Filename:  UntypedCowArrayTest.cpp
 *
 *    Description:  test array cow function
 *
 *        Version:  1.0
 *        Created:  2011-9-16 18:33:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <algorithm>
#include <cassert>

#include "UntypedArray.hpp"


using my_gl::UntypedArray;
using std::mismatch;

int main(int argc, const char *argv[])
{

     int size=100;

     int *p=new int[size];

     int byteSize=size*sizeof(int);

     UntypedArray array1(byteSize,p);

     assert(mismatch(p,p+size,array1.get<int>()).first-p==size);

     UntypedArray array2(byteSize,p);

     int *sub=new int[byteSize/2];

     array2.replace(byteSize/2,byteSize/2,sub);

     assert(mismatch(array1.get(),array1.get()+byteSize/2,array2.get()).first-array1.get()==byteSize/2);

     return 0;
}
