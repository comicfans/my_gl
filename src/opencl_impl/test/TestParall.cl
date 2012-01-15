kernel void testParall(global uint *buffer)
{
     size_t idx=get_global_id(0);
     size_t idy=get_global_id(1);
     size_t lidx=get_local_id(0);

     buffer[idx+idy*4]=(1<<idx)|(0x10<<idy);
}
