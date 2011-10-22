INCLUDE_DIRECTORIES(../../)

ADD_LIBRARY(Rasterizer Rasterizer.cpp 
     PointRasterizer.cpp 
     LineRasterizer.cpp
     TriangleRasterizer.cpp
     SimpleLineRasterizer.cpp 
     WindowCoordinates.cpp
     LineInfo.cpp)
