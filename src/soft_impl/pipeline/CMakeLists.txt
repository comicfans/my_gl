INCLUDE_DIRECTORIES(../)


SUBDIRS(clipper rasterizer interpolator index_provider test)


ADD_LIBRARY(PrimitiveIndex PrimitiveIndex.cpp)

ADD_LIBRARY(ClippedPrimitiveGroup ClippedPrimitiveGroup.cpp)

ADD_LIBRARY(Pipeline FrameBuffer.cpp)

TARGET_LINK_LIBRARIES(PrimitiveIndex IndexProvider)

TARGET_LINK_LIBRARIES(ClippedPrimitiveGroup PrimitiveIndex)

TARGET_LINK_LIBRARIES(Pipeline 
     Clipper ClippedPrimitiveGroup Rasterizer Interpolator)
