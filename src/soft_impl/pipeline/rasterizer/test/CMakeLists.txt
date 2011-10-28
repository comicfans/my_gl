INCLUDE_DIRECTORIES(../ )

ADD_EXECUTABLE(TestRasterizer TestRasterizer.cpp)
TARGET_LINK_LIBRARIES(TestRasterizer 
     TestFunction Vec4 Clipper
     Interpolator Rasterizer ClippedPrimitiveGroup Shader )

ADD_EXECUTABLE(TestLineRasterizer TestLineRasterizer.cpp)
TARGET_LINK_LIBRARIES(TestLineRasterizer 
     TestFunction Rasterizer Shader Interpolator Pipeline 
     PrimitiveIndex SoftImpl ClippedPrimitiveGroup )


ADD_TEST(RasterizerTest TestRasterizer)
ADD_TEST(LineRasterizerTest TestLineRasterizer)

