INCLUDE_DIRECTORIES(../)


SUBDIRS(clipper)


ADD_LIBRARY(PrimitiveIndex PrimitiveIndex.cpp 
     NaturalOrderIndexProvider.cpp
     IndirectOrderIndexProvider.cpp)

ADD_LIBRARY(ClippedPrimitiveGroup ClippedPrimitiveGroup.cpp)

TARGET_LINK_LIBRARIES(ClippedPrimitiveGroup PrimitiveIndex)

ADD_LIBRARY(Pipeline Interpolator.cpp)

TARGET_LINK_LIBRARIES(Pipeline Clipper ClippedPrimitiveGroup)
