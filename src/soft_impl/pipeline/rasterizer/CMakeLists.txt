INCLUDE_DIRECTORIES(../../)

ADD_LIBRARY(Rasterizer Rasterizer.cpp 
     PointRasterizer.cpp 
     LineRasterizer.cpp
     TriangleRasterizer.cpp
     SimpleLineRasterizer.cpp 
     WinCoord.cpp
     LineInfo.cpp)

SUBDIRS(test)
