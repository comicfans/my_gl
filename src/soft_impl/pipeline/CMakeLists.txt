INCLUDE_DIRECTORIES(../)


SUBDIRS(clipper rasterizer interpolator)


ADD_LIBRARY(PrimitiveIndex PrimitiveIndex.cpp 
     NaturalOrderIndexProvider.cpp
     IndirectOrderIndexProvider.cpp)

ADD_LIBRARY(ClippedPrimitiveGroup ClippedPrimitiveGroup.cpp)

ADD_LIBRARY(Pipeline)

TARGET_LINK_LIBRARIES(ClippedPrimitiveGroup PrimitiveIndex)

TARGET_LINK_LIBRARIES(Pipeline Clipper ClippedPrimitiveGroup)
