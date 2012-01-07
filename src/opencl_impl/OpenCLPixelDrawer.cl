kernel void float4ToUchar4( global float4* floatRGBA, global uchar4* ucharRGBA)
{
     size_t idxX,idxY;
     size_t sizeX,sizeY;

     idxX=get_global_id(0);
     idxY=get_global_id(1);

     sizeX=get_global_size(0);
     sizeY=get_global_size(1);

     size_t globalOffset=sizeX*idxY+idxX;

     float4 converted=floatRGBA[globalOffset]*255;

     ucharRGBA[globalOffset]=convert_uchar4(converted);

}
