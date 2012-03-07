#include "RasterizerCommon.cl" 


struct LinesIndex
{
     static int2 getIndex(int workId)
     {
	  return (int2)(workId*2,workId*2+1);
     }
};

struct LineStripIndex
{
     static int2 getIndex(int workId)
     {
	  return (int2)(workId,workId+1);
     }
};
//line loop needs vertex number info ,convert line loop to line strip is better

