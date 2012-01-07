
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})

ADD_LIBRARY(OpenCLImpl OpenCLContext.cpp)

#currently link all SoftContext stuff to OpenCLImpl Context
#will splite different library further
TARGET_LINK_LIBRARIES(OpenCLImpl 
     SoftImpl
     ${OPENCL_LIBRARY})


ADD_SUBDIRECTORY(test)
