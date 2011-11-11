ADD_EXECUTABLE(GlutTestScale GlutTestScale.cpp)

TARGET_LINK_LIBRARIES(GlutTestScale
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestScale MyGLTestScale.cpp)
TARGET_LINK_LIBRARIES(MyGLTestScale Export)

ADD_TEST(ScaleGlutTest GlutTestScale)
ADD_TEST(ScaleMyGLTest MyGLTestScale)
