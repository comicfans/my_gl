ADD_EXECUTABLE(TestOpenCLContext TestOpenCLContext.cpp)

TARGET_LINK_LIBRARIES(TestOpenCLContext OpenCLImpl)

ADD_TEST(OpenCLContextTest TestOpenCLContext)



ADD_EXECUTABLE(TestBoostInitalPath TestBoostInitalPath.cpp)
TARGET_LINK_LIBRARIES(TestBoostInitalPath ${Boost_LIBRARIES})
