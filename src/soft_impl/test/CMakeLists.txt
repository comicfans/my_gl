INCLUDE_DIRECTORIES(../)

ADD_EXECUTABLE(TestLink TestLink.cpp)
TARGET_LINK_LIBRARIES(TestLink Object Common SoftImpl Context)

ADD_EXECUTABLE(TestSDLPixelDrawer testSDLPixelDrawer.cpp)
TARGET_LINK_LIBRARIES(TestSDLPixelDrawer SoftImpl)

ADD_TEST(SDLPixelDrawerTest TestSDLPixelDrawer)




ADD_EXECUTABLE(TestSoftImpl TestSoftImpl.cpp)
TARGET_LINK_LIBRARIES(TestSoftImpl SoftImpl)

ADD_TEST(SoftImplTest TestSoftImpl)
