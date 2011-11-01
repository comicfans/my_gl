INCLUDE_DIRECTORIES(../ )

ADD_EXECUTABLE(TestRasterizer TestRasterizer.cpp)
TARGET_LINK_LIBRARIES(TestRasterizer 
     TestFunction Vec4 Clipper
     Interpolator Rasterizer ClippedPrimitiveGroup Shader )

ADD_EXECUTABLE(TestLineRasterizer TestLineRasterizer.cpp)
TARGET_LINK_LIBRARIES(TestLineRasterizer 
     TestFunction Rasterizer Shader Interpolator Pipeline 
     PrimitiveIndex SoftImpl ClippedPrimitiveGroup )

ADD_EXECUTABLE(TestWinCoord TestWinCoord.cpp)
TARGET_LINK_LIBRARIES(TestWinCoord Info)

ADD_EXECUTABLE(TestLineInfo TestLineInfo.cpp)
TARGET_LINK_LIBRARIES(TestLineInfo Info)

ADD_TEST(RasterizerTest TestRasterizer)
ADD_TEST(LineRasterizerTest TestLineRasterizer)
ADD_TEST(WinCoordTest TestWinCoord)
ADD_TEST(LineInfoTest TestLineInfo)

