INCLUDE_DIRECTORIES(../)


SUBDIRS(clipper rasterizer interpolator index_provider test)


ADD_LIBRARY(PrimitiveIndex PrimitiveIndex.cpp)

ADD_LIBRARY(ClippedPrimitiveGroup ClippedPrimitiveGroup.cpp)

ADD_LIBRARY(FrameBuffer FrameBuffer.cpp ColorBuffer.cpp DepthBuffer.cpp)

ADD_LIBRARY(Pipeline)

TARGET_LINK_LIBRARIES(PrimitiveIndex IndexProvider Common)

TARGET_LINK_LIBRARIES(ClippedPrimitiveGroup PrimitiveIndex)

TARGET_LINK_LIBRARIES(Pipeline FrameBuffer
     Clipper ClippedPrimitiveGroup Rasterizer Interpolator)
