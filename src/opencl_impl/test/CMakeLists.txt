ADD_EXECUTABLE(TestOpenCLContext TestOpenCLContext.cpp)

TARGET_LINK_LIBRARIES(TestOpenCLContext OpenCLImpl)

ADD_TEST(OpenCLContextTest TestOpenCLContext)



ADD_EXECUTABLE(TestBoostInitalPath TestBoostInitalPath.cpp)
TARGET_LINK_LIBRARIES(TestBoostInitalPath ${Boost_LIBRARIES})


ADD_EXECUTABLE(TestOpenCLPixelDrawer TestOpenCLPixelDrawer.cpp)
TARGET_LINK_LIBRARIES(TestOpenCLPixelDrawer 
     OpenCLPixelDrawer FrameBuffer Vec Info)
CHANGE_RUNNING_DIR(TestOpenCLPixelDrawer)


ADD_EXECUTABLE(TestParall TestParall.cpp)
TARGET_LINK_LIBRARIES(TestParall CLSource ${OPENCL_LIBRARY})
CHANGE_RUNNING_DIR(TestParall)
COPY_RUNTIME_FILE(TestParall.cl)
ADD_TEST(ParallTest TestParall)


ADD_EXECUTABLE(TestOpenCLCPPKernel TestOpenCLCPPKernel.cpp)
TARGET_LINK_LIBRARIES(TestOpenCLCPPKernel CLSource ${OPENCL_LIBRARY})

