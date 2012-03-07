/*
 * =====================================================================================
 *
 *       Filename:  OpenCLImageComparator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 17:21:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLImageComparator.hpp"
#include "common/image_compare/Image.hpp"

#include "opencl_impl/CLSource.hpp"

#include <utility>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <string>

#include <boost/assert.hpp>

using std::vector;
using std::string;
namespace my_gl {

     OpenCLImageComparator::OpenCLImageComparator()
     {
	  _context=cl::Context(CL_DEVICE_TYPE_DEFAULT);

	  vector<cl::Device> devices=_context.getInfo<CL_CONTEXT_DEVICES>();

	  CLSource source("ImageComparator.cl");

	  _program=cl::Program(_context,source.getSources());

	  string options;

	  _program.build(devices,options.c_str());

	  _commandQueue=cl::CommandQueue(_context,devices[0]);

	  _recursionAverageKernel=cl::Kernel(_program,"recursionAverage");
	  _RGBPreprocessKernel=cl::Kernel(_program,"RGBPreprocess");
	  _recursionSumKernel=cl::Kernel(_program,"recursionSum");
	  _calculateSimilarKernel=cl::Kernel(_program,"calculateSimilar");

     }

     double OpenCLImageComparator::clBufferFloatSum(cl::Buffer buffer, int floatElementNumber)
     {
	  void *voidP=_commandQueue.enqueueMapBuffer
	       (buffer,CL_TRUE,CL_MAP_READ,0,
		    floatElementNumber*sizeof(float));

	  float* averageValuesFloat=reinterpret_cast<float*>(voidP);

	  double sum=
	  std::accumulate<float*,double>(averageValuesFloat,
		    averageValuesFloat+floatElementNumber,0.0d);

	  _commandQueue.enqueueUnmapMemObject(buffer,voidP);

	  return sum;
     }

     void OpenCLImageComparator::imagePreprocess(Image& image,cl::Buffer& grayValueBuffer,double& averageGray)
     {
	  int pixelNumber=image.width*image.height;
	  //preprocess rgb to gray first


	  cl::Buffer rgbBuffer(_context,CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
		    image.byteSize(),image.rawData());

	  grayValueBuffer=cl::Buffer(_context,CL_MEM_WRITE_ONLY,
		    pixelNumber*sizeof(float),nullptr);

	  _RGBPreprocessKernel.setArg(0,rgbBuffer);
	  _RGBPreprocessKernel.setArg(1,grayValueBuffer);

	  //enter command queue,use 1D 
	  //
	  _commandQueue.enqueueNDRangeKernel(_RGBPreprocessKernel,
		    cl::NullRange,
		    cl::NDRange(pixelNumber),
		    cl::NDRange(1));

	  _commandQueue.enqueueBarrier();
	  //rgb data is transfered to gray value 

	  auto minMaxValue=std::minmax(image.height,image.width);

	  int elementPerItem=minMaxValue.first;
	  int workItemNumber=minMaxValue.second;

	  cl::Buffer averageBuffer(_context,CL_MEM_WRITE_ONLY,
		    workItemNumber*sizeof(float),nullptr);

	  _recursionAverageKernel.setArg
	       (0,cl_int(elementPerItem));

	  _recursionAverageKernel.setArg(1,grayValueBuffer);

	  _recursionAverageKernel.setArg(2,averageBuffer);

	  _commandQueue.enqueueNDRangeKernel(_recursionAverageKernel,
		    cl::NullRange,
		    cl::NDRange(workItemNumber),		    
		    cl::NDRange(1));

	  //now average gray is transfered into averageBuffer
	  _commandQueue.enqueueBarrier();
	  double sum=clBufferFloatSum(averageBuffer,workItemNumber);

	  averageGray=sum/workItemNumber;

     }

     double OpenCLImageComparator::compare(Image &image1, Image &image2)
     {
	  cl::Buffer grayValueBuffer1,
	       grayValueBuffer2;

	  double averageGray1,
		averageGray2;

	  imagePreprocess(image1,grayValueBuffer1,averageGray1);
	  imagePreprocess(image2,grayValueBuffer2,averageGray2);

	  int pixelNumber=image1.width*image1.height;

	  _calculateSimilarKernel.setArg(0,grayValueBuffer1);
	  _calculateSimilarKernel.setArg(1,cl_float(averageGray1));
	  _calculateSimilarKernel.setArg(2,grayValueBuffer2);
	  _calculateSimilarKernel.setArg(3,cl_float(averageGray2));

	  cl::Buffer numeratorBuffer(_context,CL_MEM_WRITE_ONLY,pixelNumber*sizeof(float),nullptr),
	       denominatorLeftSqBuffer(_context,CL_MEM_WRITE_ONLY,pixelNumber*sizeof(float),nullptr),
	       denominatorRightSqBuffer(_context,CL_MEM_WRITE_ONLY,pixelNumber*sizeof(float),nullptr);

	  _calculateSimilarKernel.setArg(4,numeratorBuffer);
	  _calculateSimilarKernel.setArg(5,denominatorLeftSqBuffer);
	  _calculateSimilarKernel.setArg(6,denominatorRightSqBuffer);

	  _commandQueue.enqueueNDRangeKernel(_calculateSimilarKernel,
		    cl::NullRange,
		    cl::NDRange(pixelNumber),
		    cl::NDRange(1));


	  int workItemNumber=std::max(image1.width,image1.height),
	      itemProcessNumber=std::min(image1.width,image1.height);

	  cl::Buffer resultNumeratorBuffer(_context,CL_MEM_WRITE_ONLY,workItemNumber*sizeof(float),nullptr),
	       resultDenominatorLeftSqBuffer(_context,CL_MEM_WRITE_ONLY,workItemNumber*sizeof(float),nullptr),
	       resultDenominatorRightSqBuffer(_context,CL_MEM_WRITE_ONLY,workItemNumber*sizeof(float),nullptr);


	  _recursionSumKernel.setArg(0,cl_int(itemProcessNumber));

	  _recursionSumKernel.setArg(1,numeratorBuffer);
	  _recursionSumKernel.setArg(2,denominatorLeftSqBuffer);
	  _recursionSumKernel.setArg(3,denominatorRightSqBuffer);

	  _recursionSumKernel.setArg(4,resultNumeratorBuffer);
	  _recursionSumKernel.setArg(5,resultDenominatorLeftSqBuffer);
	  _recursionSumKernel.setArg(6,resultDenominatorRightSqBuffer);

	  _commandQueue.enqueueBarrier();

	  _commandQueue.enqueueNDRangeKernel(_recursionSumKernel,
		    cl::NullRange,
		    cl::NDRange(workItemNumber),
		    cl::NDRange(1));

	  _commandQueue.enqueueBarrier();

	  double finalNumerator=clBufferFloatSum(resultNumeratorBuffer,workItemNumber),
		finalDenominatorLeftSq=clBufferFloatSum(resultDenominatorLeftSqBuffer,workItemNumber),
		finalDenominatorRightSq=clBufferFloatSum(resultDenominatorRightSqBuffer,workItemNumber);

	  double finalDenominator=sqrt(finalDenominatorLeftSq*finalDenominatorRightSq);
	  if( (finalDenominator==0) && (finalNumerator==0))
	  {
	       return 1;
	  }
	  
	  if(finalDenominator==0)
	  {
	       return DBL_MAX;
	  }
	  
	  return finalNumerator/finalDenominator;
     }

     OpenCLImageComparator::~OpenCLImageComparator()
     {}
	
} /* my_gl */
