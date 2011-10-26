INCLUDE_DIRECTORIES(../../)
ADD_EXECUTABLE(TestVec4Size Vec4SizeTest.cpp)

ADD_LIBRARY(TestFunction TestFunction.cpp)
TARGET_LINK_LIBRARIES(TestFunction Vec4)
