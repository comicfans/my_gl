INCLUDE_DIRECTORIES(../)

ADD_EXECUTABLE(TestLink TestLink.cpp)

TARGET_LINK_LIBRARIES(TestLink Object Common SoftImpl)

ADD_EXECUTABLE(TestSDLPixelDrawer testSDLPixelDrawer.cpp)

TARGET_LINK_LIBRARIES(TestSDLPixelDrawer SoftImpl)

ADD_TEST(SDLPixelDrawerTest TestSDLPixelDrawer)
