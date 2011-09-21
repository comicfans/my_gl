INCLUDE_DIRECTORIES(../soft_impl)

ADD_LIBRARY(Vector Vector.cpp)

ADD_LIBRARY(Matrix Matrix.cpp MatrixStack.cpp)

ADD_LIBRARY(VectorManager VectorManager.cpp)


ADD_LIBRARY(VectorProvider 
     VectorProvider.cpp
     UniqueVectorProvider.cpp 
     ArrayVectorProvider.cpp
     BufferObjectVectorProvider.cpp
     ClientArrayVectorProvider.cpp
     )
TARGET_LINK_LIBRARIES(VectorProvider Vector)

TARGET_LINK_LIBRARIES(VectorManager VectorProvider)

ADD_LIBRARY(Context Context.cpp)

ADD_LIBRARY(Common UntypedArray.cpp PixelUnpacker.cpp )

ADD_EXECUTABLE(VectorReaderTest VectorReaderTest.cpp)
TARGET_LINK_LIBRARIES(VectorReaderTest Common)

ADD_EXECUTABLE(UntypedCowArrayTest UntypedCowArrayTest.cpp)
TARGET_LINK_LIBRARIES(UntypedCowArrayTest Common)

ADD_EXECUTABLE(VectorTest VectorTest.cpp)
TARGET_LINK_LIBRARIES(VectorTest Common)

ADD_TEST(Test1 UntypedCowArrayTest)
ADD_TEST(Test2 VectorReaderTest)
ADD_TEST(Test3 VectorTest)

