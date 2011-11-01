INCLUDE_DIRECTORIES(../../)

ADD_LIBRARY(Info WinCoord.cpp LineInfo.cpp)

ADD_LIBRARY(Rasterizer Rasterizer.cpp 
     PointRasterizer.cpp 
     LineRasterizer.cpp
     TriangleRasterizer.cpp
     SimpleLineRasterizer.cpp )

TARGET_LINK_LIBRARIES(Rasterizer Info)

SUBDIRS(test)
