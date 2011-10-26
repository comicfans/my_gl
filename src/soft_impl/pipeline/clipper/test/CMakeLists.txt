INCLUDE_DIRECTORIES(../ ../../../)

ADD_EXECUTABLE(testLineClipper testLineClipper.cpp)

TARGET_LINK_LIBRARIES(testLineClipper 
     Clipper Interpolator 
     TestFunction ClippedPrimitiveGroup
     Shader)

ADD_TEST(LineClipperTest testLineClipper)
