/*
 * =====================================================================================
 *
 *       Filename:  VectorReaderTest.cpp
 *
 *    Description:  test vector reader template instantiation
 *
 *        Version:  1.0
 *        Created:  2011-9-16 18:28:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "AlignedValueVectorReader.hpp"

using my_gl::AlignedValueVectorReader;
using my_gl::UntypedCowArray;

int main(int argc, const char *argv[])
{
     int size=100;

     float *p=new float[size];

     p[0]=1;
     p[1]=2;
     p[2]=3;
     p[3]=4;
     p[4]=5;
     p[5]=6;

     int byteSize=size*sizeof(float);

     UntypedCowArray array1(byteSize,p);

     AlignedValueVectorReader<float> floatReader(array1,4,0,0);


     assert(floatReader.values()[0]==p[0]);

     floatReader.next();

     assert(floatReader.values()[0]==p[4]);

     AlignedValueVectorReader<float> floatReader2(array1,3,4,0);

     assert(floatReader2.values()[0]==p[1]);

     floatReader2.next();

     assert(floatReader2.values()[0]==p[4]);

}
