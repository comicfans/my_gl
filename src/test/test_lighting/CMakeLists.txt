ADD_EXECUTABLE(GlutTestLighting GlutTestLighting.cpp)

TARGET_LINK_LIBRARIES(GlutTestLighting
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestLighting MyGLTestLighting.cpp)
TARGET_LINK_LIBRARIES(MyGLTestLighting Export)

ADD_TEST(LightingGlutTest GlutTestLighting)
ADD_TEST(LightingMyGLTest MyGLTestLighting)
