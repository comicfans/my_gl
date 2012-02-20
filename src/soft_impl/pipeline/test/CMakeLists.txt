INCLUDE_DIRECTORIES(../../)
ADD_EXECUTABLE(TestClippedPrimitiveGroup 
     TestClippedPrimitiveGroup.cpp)

TARGET_LINK_LIBRARIES(TestClippedPrimitiveGroup 
     ClippedPrimitiveGroup Shader TestFunction Common)

ADD_TEST(ClippedPrimitiveGroupTest TestClippedPrimitiveGroup)
