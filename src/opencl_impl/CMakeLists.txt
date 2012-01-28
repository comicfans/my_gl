
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})

ADD_DEFINITIONS(-D__CL_ENABLE_EXCEPTIONS)

ADD_LIBRARY(CLSource CLSource.cpp)
TARGET_LINK_LIBRARIES(CLSource ${Boost_LIBRARIES})

ADD_LIBRARY(OpenCLPixelDrawer OpenCLPixelDrawer.cpp)
TARGET_LINK_LIBRARIES(OpenCLPixelDrawer ${OPENCL_LIBRARY} 
     SDLPixelDrawer CLSource )


ADD_LIBRARY(OpenCLImpl OpenCLContext.cpp)

#currently link all SoftContext stuff to OpenCLImpl Context
#will splite different library further
TARGET_LINK_LIBRARIES(OpenCLImpl 
     SoftImpl
     OpenCLPixelDrawer
     ${OPENCL_LIBRARY})


ADD_SUBDIRECTORY(test)


FILE(GLOB_RECURSE openCLSources *.cl)
COPY_RUNTIME_FILE(${openCLSources})

ADD_SUBDIRECTORY(pipeline)
ADD_SUBDIRECTORY(shader)

