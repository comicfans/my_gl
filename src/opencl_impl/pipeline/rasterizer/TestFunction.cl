
bool orderTest(int thisOrder,global int *intZBuffer)
{

#ifndef NDEBUG
     return thisOrder>*intZBuffer;
#else
     return atomic_max(intZBuffer,thisOrder) < thisOrder;
#endif

}


bool depthLessTest(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ<*reinterpretIntZPtr;
#else
     return atomic_min(reinterpretIntZPtr,reinterpretIntZ) > reinterpretIntZ;
#endif
}


bool depthLessEqualTest(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ<=*reinterpretIntZPtr;
#else
     return atomic_min(reinterpretIntZPtr,reinterpretIntZ) >= reinterpretIntZ;
#endif
}


bool depthGreaterTest(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ>*reinterpretIntZPtr;
#else
     return atomic_max(reinterpretIntZPtr,reinterpretIntZ) < reinterpretIntZ;
#endif
}


bool depthGreaterEqualTest(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ>=*reinterpretIntZPtr;
#else
     return atomic_max(reinterpretIntZPtr,reinterpretIntZ) <= reinterpretIntZ;
#endif
}

bool depthEqualTest(int reinterpretIntZ,global int *reinterpretIntZPtr)
{
	return reinterpretIntZ==*reinterpretIntZPtr;
}

bool depthNotEqualTest(int reinterpretIntZ,global int *reinterpretIntZPtr)
{
#ifndef NDEBUG
     return reinterpretIntZ!=*reinterpretIntZPtr;
#else
     return atomic_xchg(reinterpretIntZPtr,reinterpretIntZ) != reinterpretIntZ;
#endif
}

