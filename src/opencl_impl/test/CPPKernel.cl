

class Func1{
     public:
	  static void func(int value)

	  {
	       int bbes=value*3;
	       bbes +=3245;
	  }

};

class Func2{
     public:
     static void func(int value)
     {
	  int sgasd=value*32;

	  sgasd+=3;
     }
};

     template<class T>
kernel void cppKernel(int value)
{
     T::func(value);
}


template
kernel void __attribute__((mangled_name(cppKernelFunc1))) cppKernel<Func1>(int value);

