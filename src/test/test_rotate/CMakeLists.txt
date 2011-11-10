INCLUDE_DIRECTORIES(../ ../test_client_vertex_pointer/)

ADD_EXECUTABLE(GlutTestRotate GlutTestRotate.cpp)

TARGET_LINK_LIBRARIES(GlutTestRotate
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestRotate MyGLTestRotate.cpp)
TARGET_LINK_LIBRARIES(MyGLTestRotate Export)

ADD_TEST(RotateGlutTest GlutTestRotate)
ADD_TEST(RotateMyGLTest MyGLTestRotate)
