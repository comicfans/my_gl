INCLUDE_DIRECTORIES(../ )

ADD_EXECUTABLE(TestRasterizer TestRasterizer.cpp)
TARGET_LINK_LIBRARIES(TestRasterizer 
     TestFunction Vec4 Clipper
     Interpolator Rasterizer ClippedPrimitiveGroup Shader )

ADD_TEST(RasterizerTest TestRasterizer)

