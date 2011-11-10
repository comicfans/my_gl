ADD_EXECUTABLE(GlutTestClientArrayPointer GlutTestClientArrayPointer.cpp)

TARGET_LINK_LIBRARIES(GlutTestClientArrayPointer
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestClientArrayPointer MyGLTestClientArrayPointer.cpp)
TARGET_LINK_LIBRARIES(MyGLTestClientArrayPointer Export)

ADD_TEST(ClientArrayPointerTestGlut GlutTestClientArrayPointer)
ADD_TEST(ClientArrayPointerTestMyGL MyGLTestClientArrayPointer)
