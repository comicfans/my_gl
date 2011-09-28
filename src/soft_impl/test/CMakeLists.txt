INCLUDE_DIRECTORIES(../)

ADD_EXECUTABLE(TestLink TestLink.cpp)

TARGET_LINK_LIBRARIES(TestLink Object Common SoftImpl)
