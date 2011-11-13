ADD_EXECUTABLE(GlutTestDrawElements GlutTestDrawElements.cpp)

TARGET_LINK_LIBRARIES(GlutTestDrawElements
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestDrawElements MyGLTestDrawElements.cpp)
TARGET_LINK_LIBRARIES(MyGLTestDrawElements Export)

ADD_TEST(DrawElementsGlutTest GlutTestDrawElements)
ADD_TEST(DrawElementsMyGLTest MyGLTestDrawElements)
