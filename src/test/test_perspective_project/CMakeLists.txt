ADD_EXECUTABLE(GlutTestPerspectiveProject GlutTestPerspectiveProject.cpp)

TARGET_LINK_LIBRARIES(GlutTestPerspectiveProject
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestPerspectiveProject MyGLTestPerspectiveProject.cpp)
TARGET_LINK_LIBRARIES(MyGLTestPerspectiveProject Export)

ADD_TEST(PerspectiveProjectGlutTest GlutTestPerspectiveProject)
ADD_TEST(PerspectiveProjectMyGLTest MyGLTestPerspectiveProject)
