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

ADD_EXECUTABLE(GlutTestSpotLight GlutTestSpotLight.cpp)
TARGET_LINK_LIBRARIES(GlutTestSpotLight
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES})

ADD_EXECUTABLE(MyGLTestSpotLight MyGLTestSpotLight.cpp)
TARGET_LINK_LIBRARIES(MyGLTestSpotLight Export)


ADD_EXECUTABLE(GlutTestInfinitePointLight 
     GlutTestInfinitePointLight.cpp)
TARGET_LINK_LIBRARIES(GlutTestInfinitePointLight
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES})

ADD_EXECUTABLE(MyGLTestInfinitePointLight 
     MyGLTestInfinitePointLight.cpp)
TARGET_LINK_LIBRARIES(MyGLTestInfinitePointLight Export)




ADD_TEST(LightingGlutTest GlutTestLighting)
ADD_TEST(LightingMyGLTest MyGLTestLighting)

ADD_TEST(MovingLightGlutTest GlutTestMovingLight)
ADD_TEST(MovingLightMyGLTest MyGLTestMovingLight)

ADD_TEST(SpotLightGlutTest GlutTestSpotLight)
ADD_TEST(SpotLightMyGLTest MyGLTestSpotLight)

ADD_TEST(InfinitePointLightGlutTest GlutTestInfinitePointLight)
ADD_TEST(InfinitePointLightMyGLTest MyGLTestInfinitePointLight)
