
struct OrderTest
{
static bool test(int thisOrder,global int *intZBuffer)
{

#ifndef NDEBUG
     return thisOrder>*intZBuffer;
#else
     return atomic_max(intZBuffer,thisOrder) < thisOrder;
#endif

}
};


struct LessTest
{
static bool test(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ<*reinterpretIntZPtr;
#else
     return atomic_min(reinterpretIntZPtr,reinterpretIntZ) > reinterpretIntZ;
#endif
}
};


struct LessEqualTest
{
static bool test(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ<=*reinterpretIntZPtr;
#else
     return atomic_min(reinterpretIntZPtr,reinterpretIntZ) >= reinterpretIntZ;
#endif
}
};

struct GreaterTest{
static bool test(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ>*reinterpretIntZPtr;
#else
     return atomic_max(reinterpretIntZPtr,reinterpretIntZ) < reinterpretIntZ;
#endif
}
};

struct GreaterEqualTest{
static bool test(int reinterpretIntZ,global int *reinterpretIntZPtr)
{

#ifndef NDEBUG
     return reinterpretIntZ>=*reinterpretIntZPtr;
#else
     return atomic_max(reinterpretIntZPtr,reinterpretIntZ) <= reinterpretIntZ;
#endif
}
};

struct EqualTest
{
static bool test(int reinterpretIntZ,global int *reinterpretIntZPtr)
{
	return reinterpretIntZ==*reinterpretIntZPtr;
}};

struct NotEqualTest
{
static bool test(int reinterpretIntZ,global int *reinterpretIntZPtr)
{
#ifndef NDEBUG
     return reinterpretIntZ!=*reinterpretIntZPtr;
#else
     return atomic_xchg(reinterpretIntZPtr,reinterpretIntZ) != reinterpretIntZ;
#endif
}
};

