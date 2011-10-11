INCLUDE_DIRECTORIES(../)

SUBDIRS(clipper)

ADD_LIBRARY(PrimitiveIndex PrimitiveIndex.cpp 
     NaturalOrderIndexProvider.cpp
     IndirectOrderIndexProvider.cpp)

ADD_LIBRARY(Pipeline Interpolator.cpp)

TARGET_LINK_LIBRARIES(Pipeline Clipper PrimitiveIndex)
