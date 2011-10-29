INCLUDE_DIRECTORIES(../../)
ADD_EXECUTABLE(TestVertexAttributeBuffer TestVertexAttributeBuffer.cpp)

TARGET_LINK_LIBRARIES(TestVertexAttributeBuffer Shader Vec4)

ADD_TEST(VertexAttributeBufferTest TestVertexAttributeBuffer )
