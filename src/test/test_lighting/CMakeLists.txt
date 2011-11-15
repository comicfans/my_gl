ADD_EXECUTABLE(GlutTestLighting GlutTestLighting.cpp)

TARGET_LINK_LIBRARIES(GlutTestLighting
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestLighting MyGLTestLighting.cpp)
TARGET_LINK_LIBRARIES(MyGLTestLighting Export)


ADD_EXECUTABLE(GlutTestMovingLight GlutTestMovingLight.cpp)
TARGET_LINK_LIBRARIES(GlutTestMovingLight
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES})

ADD_EXECUTABLE(MyGLTestMovingLight MyGLTestMovingLight.cpp)
TARGET_LINK_LIBRARIES(MyGLTestMovingLight Export)

ADD_TEST(LightingGlutTest GlutTestLighting)
ADD_TEST(LightingMyGLTest MyGLTestLighting)

ADD_TEST(MovingLightGlutTest GlutTestMovingLight)
ADD_TEST(MovingLightMyGLTest MyGLTestMovingLight)
