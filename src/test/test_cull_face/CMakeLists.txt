ADD_EXECUTABLE(GlutTestCullFace GlutTestCullFace.cpp)

TARGET_LINK_LIBRARIES(GlutTestCullFace
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestCullFace MyGLTestCullFace.cpp)
TARGET_LINK_LIBRARIES(MyGLTestCullFace Export)

ADD_TEST(CullFaceGlutTest GlutTestCullFace)
ADD_TEST(CullFaceMyGLTest MyGLTestCullFace)



ADD_EXECUTABLE(GlutTestCullFaceBack GlutTestCullFaceBack.cpp)

TARGET_LINK_LIBRARIES(GlutTestCullFaceBack
     GlutInit
     ${GLEW_LIBRARY}
     ${GLUT_LIBRARY}
     ${OPENGL_LIBRARIES}
     ) 

ADD_EXECUTABLE(MyGLTestCullFaceBack MyGLTestCullFaceBack.cpp)
TARGET_LINK_LIBRARIES(MyGLTestCullFaceBack Export)

ADD_TEST(CullFaceBackGlutTest GlutTestCullFaceBack)
ADD_TEST(CullFaceBackMyGLTest MyGLTestCullFaceBack)
