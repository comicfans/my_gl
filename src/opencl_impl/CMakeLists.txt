
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})

ADD_DEFINITIONS(-DCL_USE_DEPRECATED_OPENCL_1_1_APIS)

ADD_LIBRARY(CLSource CLSource.cpp)
TARGET_LINK_LIBRARIES(CLSource ${Boost_LIBRARIES})

ADD_LIBRARY(OpenCLPixelDrawer OpenCLPixelDrawer.cpp)
TARGET_LINK_LIBRARIES(OpenCLPixelDrawer ${OPENCL_LIBRARY} 
     SDLPixelDrawer CLSource )


ADD_LIBRARY(OpenCLImpl OpenCLContext.cpp)

#currently link all SoftContext stuff to OpenCLImpl Context
#will splite different library further
TARGET_LINK_LIBRARIES(OpenCLImpl 
     OpenCLPixelDrawer
     CLRasterizer
     OpenCLShader
     OpenCLClippedPrimitiveGroup
     OpenCLFrameBuffer
     SoftImpl
     ${OPENCL_LIBRARY})


ADD_SUBDIRECTORY(test)


FILE(GLOB_RECURSE openCLSources *.cl)
COPY_RUNTIME_FILE(${openCLSources})

ADD_SUBDIRECTORY(pipeline)
ADD_SUBDIRECTORY(shader)

