INCLUDE_DIRECTORIES(../ ../../../)

ADD_EXECUTABLE(testLineClipper testLineClipper.cpp)
ADD_EXECUTABLE(testPointClipper testPointClipper.cpp)

TARGET_LINK_LIBRARIES(testLineClipper 
     Clipper Interpolator 
     TestFunction ClippedPrimitiveGroup
     Shader)

TARGET_LINK_LIBRARIES(testPointClipper
     Clipper Interpolator
     TestFunction ClippedPrimitiveGroup
     Shader
     )


ADD_TEST(LineClipperTest testLineClipper)
ADD_TEST(PointClipperTest testPointClipper)
