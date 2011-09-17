SET (Common_Src Matrix.cpp MatrixStack.cpp UntypedCowArray.cpp
     Vector.cpp AlignedValueVectorReader.cpp)

ADD_LIBRARY(Common ${Common_Src})

ADD_EXECUTABLE(VectorReaderTest VectorReaderTest.cpp)
TARGET_LINK_LIBRARIES(VectorReaderTest Common)

ADD_EXECUTABLE(UntypedCowArrayTest UntypedCowArrayTest.cpp)
TARGET_LINK_LIBRARIES(UntypedCowArrayTest Common)

ADD_TEST(Test1 UntypedCowArrayTest)
ADD_TEST(Test2 VectorReaderTest)
