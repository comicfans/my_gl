
/** 
 * @brief process RGB data to gray value[0~1] ,
 * 
 * @param rgbaData rgba data of pixel
 * @param grayResult gray value of pixel
 * @param grayAverage group average gray value
 * 
 */
kernel void RGBPreprocess(
	  global unsigned char * rgbaData,
	  global float * grayResult
	  )
{
     int workId=get_global_id(0);

     float grayValue=dot(convert_float3(
		    vload4(workId,rgbaData).xyz),
	       (float3)(0.3,0.59,0.11))/255;

     grayResult[workId]=grayValue;

}

kernel void recursionAverage(int number,
	  global float * prevResult,
	  global float* thisResult)
{
     int workId=get_global_id(0);

     int beginIndex=workId*number;

     float sum=0;

     for(int i=0;i<number;++i)
     {
	  sum+=prevResult[beginIndex];
     }

     thisResult[workId]=sum/number;
}

kernel void calculateSimilar(global float* grayImage1,
	  const float averageGray1,
	  global float* grayImage2,
	  const float averageGray2,
	  global float *numerator,
	  global float *denominatorLeftSq,
	  global float *denominatorRightSq)
{
     int workId=get_global_id(0);

     float grayValue1=grayImage1[workId],
	   grayValue2=grayImage2[workId];

     numerator[workId]=(grayValue1-averageGray1)*(grayValue2-averageGray2);

     denominatorLeftSq[workId]=pow(grayValue1-averageGray1,2.0f);
     denominatorRightSq[workId]=pow(grayValue2-averageGray2,2.0f);
}


kernel void recursionSum(int number,
	  global float* prevNumerator,
	  global float* prevDenominatorLeftSq,
	  global float* prevDenominatorRightSq,

	  global float* thisNumerator,
	  global float* thisDenominatorLeftSq,
	  global float* thisDenominatorRightSq
	  )
{
     float numerator=0,
     denominatorLeftSq=0,
     denominatorRightSq=0;

     int workId=get_global_id(0);

     int beginIndex=number*workId;

     for(int i=0;i<number;++i)
     {
	  numerator+=prevNumerator[beginIndex+i];
	  denominatorLeftSq+=prevDenominatorLeftSq[beginIndex+i];
	  denominatorRightSq+=prevDenominatorRightSq[beginIndex+i];
     }

     thisNumerator[workId]=numerator;
     thisDenominatorLeftSq[workId]=denominatorLeftSq;
     thisDenominatorRightSq[workId]=denominatorRightSq;
}


