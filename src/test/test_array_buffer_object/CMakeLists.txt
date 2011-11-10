ADD_EXECUTABLE(GlutTestArrayBufferObject GlutTest.cpp)

TARGET_LINK_LIBRARIES(GlutTestArrayBufferObject 
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestArrayBufferObject MyGLTestArrayBufferObject.cpp)
TARGET_LINK_LIBRARIES(MyGLTestArrayBufferObject Export)

ADD_TEST(ArrayBufferObjectTestGlut GlutTestArrayBufferObject)
ADD_TEST(ArrayBufferObjectTestMyGL MyGLTestArrayBufferObject)
