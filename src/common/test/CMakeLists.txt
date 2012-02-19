INCLUDE_DIRECTORIES(../../)
ADD_EXECUTABLE(TestVec4Size Vec4SizeTest.cpp)


ADD_LIBRARY(TestFunction TestFunction.cpp)
TARGET_LINK_LIBRARIES(TestFunction Vec Matrix)

ADD_EXECUTABLE(TestVec TestVec4.cpp)
TARGET_LINK_LIBRARIES(TestVec TestFunction)

ADD_EXECUTABLE(TestMatrixInverse TestMatrixInverse.cpp)
TARGET_LINK_LIBRARIES(TestMatrixInverse TestFunction Matrix Vec )

ADD_EXECUTABLE(TestMatrixTranspose TestMatrixTranspose.cpp)
TARGET_LINK_LIBRARIES(TestMatrixTranspose  TestFunction Matrix Vec)

ADD_EXECUTABLE(TestMatrix testMatrix.cpp)
TARGET_LINK_LIBRARIES(TestMatrix TestFunction Matrix Vec)

ADD_EXECUTABLE(TestMatrixRowColumnValue TestMatrixRowColumnValue.cpp)
TARGET_LINK_LIBRARIES(TestMatrixRowColumnValue TestFunction Matrix Vec)

ADD_EXECUTABLE(TestVecLink TestVecLink.cpp)
TARGET_LINK_LIBRARIES(TestVecLink Vec Matrix)

ADD_EXECUTABLE(TestMatrixVecMul TestMatrixVecMul.cpp)
TARGET_LINK_LIBRARIES(TestMatrixVecMul TestFunction Matrix Vec)

ADD_EXECUTABLE(TestMatrixMul TestMatrixMul.cpp)
TARGET_LINK_LIBRARIES(TestMatrixMul TestFunction Matrix Vec)

ADD_EXECUTABLE(TestClientArrayVec4Provider TestClientArrayVec4Provider.cpp)
TARGET_LINK_LIBRARIES(TestClientArrayVec4Provider Vec4Provider Common)


ADD_EXECUTABLE(TestVecNormalize TestVecNormalize.cpp)
TARGET_LINK_LIBRARIES(TestVecNormalize TestFunction Vec)

ADD_TEST(Vec4Test TestVec)
ADD_TEST(MatrixTest TestMatrix)
ADD_TEST(ClientArrayVec4ProviderTest TestClientArrayVec4Provider)
ADD_TEST(MatrixTransposeTest TestMatrixTranspose)
ADD_TEST(MatrixInverseTest TestMatrixInverse)
ADD_TEST(MatrixRowColumnTest TestMatrixRowColumnValue)
ADD_TEST(MatrixVecMulTest TestMatrixVecMul)
ADD_TEST(MatrixMulTest TestMatrixMul)
ADD_TEST(VecNormalizeTest TestVecNormalize)

