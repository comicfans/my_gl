INCLUDE_DIRECTORIES(../../)
ADD_EXECUTABLE(TestVertexAttributeBuffer TestVertexAttributeBuffer.cpp)

TARGET_LINK_LIBRARIES(TestVertexAttributeBuffer Shader Vec)

ADD_TEST(VertexAttributeBufferTest TestVertexAttributeBuffer )
