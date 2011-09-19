
ADD_LIBRARY(Vector Vector.cpp)

ADD_LIBRARY(Matrix Matrix.cpp MatrixStack.cpp)

ADD_LIBRARY(VectorProvider 
     UniqueVectorProvider.cpp 
     ArrayVectorProvider.cpp
     ClientArrayVectorProvider.cpp
     )
ADD_LIBRARY(VectorManager VectorManager.cpp)

TARGET_LINK_LIBRARIES(VectorProvider Vector)

TARGET_LINK_LIBRARIES(VectorManager VectorProvider)

ADD_LIBRARY(Common UntypedArray.cpp PixelUnpacker.cpp)

ADD_EXECUTABLE(VectorReaderTest VectorReaderTest.cpp)
TARGET_LINK_LIBRARIES(VectorReaderTest Common)

ADD_EXECUTABLE(UntypedCowArrayTest UntypedCowArrayTest.cpp)
TARGET_LINK_LIBRARIES(UntypedCowArrayTest Common)

ADD_EXECUTABLE(VectorTest VectorTest.cpp)
TARGET_LINK_LIBRARIES(VectorTest Common)

ADD_TEST(Test1 UntypedCowArrayTest)
ADD_TEST(Test2 VectorReaderTest)
ADD_TEST(Test3 VectorTest)

