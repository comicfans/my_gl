INCLUDE_DIRECTORIES(../../)
ADD_EXECUTABLE(TestVec4Size Vec4SizeTest.cpp)


ADD_LIBRARY(TestFunction TestFunction.cpp)
TARGET_LINK_LIBRARIES(TestFunction Vec4 Matrix)

ADD_EXECUTABLE(TestVec4 TestVec4.cpp)
TARGET_LINK_LIBRARIES(TestVec4 TestFunction)

ADD_EXECUTABLE(TestMatrix testMatrix.cpp)
TARGET_LINK_LIBRARIES(TestMatrix TestFunction)

ADD_TEST(Vec4Test TestVec4)
ADD_TEST(MatrixTest TestMatrix)

