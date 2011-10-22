INCLUDE_DIRECTORIES(../)


SUBDIRS(clipper rasterizer interpolator index_provider)


ADD_LIBRARY(PrimitiveIndex PrimitiveIndex.cpp)

ADD_LIBRARY(ClippedPrimitiveGroup ClippedPrimitiveGroup.cpp)

ADD_LIBRARY(Pipeline)

TARGET_LINK_LIBRARIES(PrimitiveIndex IndexProvider)

TARGET_LINK_LIBRARIES(ClippedPrimitiveGroup PrimitiveIndex)

TARGET_LINK_LIBRARIES(Pipeline Clipper ClippedPrimitiveGroup)
