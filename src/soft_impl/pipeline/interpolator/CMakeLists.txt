INCLUDE_DIRECTORIES(../../)
ADD_LIBRARY(Interpolator Interpolator.cpp 
     CoordInfo.cpp
     WinCoordInterpolator.cpp)

TARGET_LINK_LIBRARIES(Interpolator Info)
