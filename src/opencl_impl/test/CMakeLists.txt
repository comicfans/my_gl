ADD_EXECUTABLE(TestOpenCLContext TestOpenCLContext.cpp)

TARGET_LINK_LIBRARIES(TestOpenCLContext OpenCLImpl)

ADD_TEST(OpenCLContextTest TestOpenCLContext)



ADD_EXECUTABLE(TestBoostInitalPath TestBoostInitalPath.cpp)
TARGET_LINK_LIBRARIES(TestBoostInitalPath ${Boost_LIBRARIES})


ADD_EXECUTABLE(TestOpenCLPixelDrawer TestOpenCLPixelDrawer.cpp)
TARGET_LINK_LIBRARIES(TestOpenCLPixelDrawer 
     OpenCLPixelDrawer FrameBuffer Vec Info)
CHANGE_RUNNING_DIR(TestOpenCLPixelDrawer)
