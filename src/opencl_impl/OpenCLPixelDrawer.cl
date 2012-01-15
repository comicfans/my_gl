kernel void float4ToUchar4( global float4* floatRGBA, global uchar4* ucharRGBA)
{
     size_t idxX,idxY;
     size_t sizeX;

     idxX=get_global_id(1);
     idxY=get_global_id(0);

     sizeX=get_global_size(1);

     size_t globalOffset=sizeX*idxY+idxX;

     ucharRGBA[globalOffset].xyz=
	  convert_uchar3(floatRGBA[globalOffset].xyz*255);

}
