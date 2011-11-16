INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rd/EasyBMP)

ADD_EXECUTABLE(GlutTestTexture GlutTestTexture.cpp)
TARGET_LINK_LIBRARIES(GlutTestTexture
     GlutInit
     ${GLUT_LIBRARY}
     ${GLEW_LIBRARY}
     ${OPENGL_LIBRARIES})

ADD_EXECUTABLE(MyGLTestTexture MyGLTestTexture.cpp)
TARGET_LINK_LIBRARIES(MyGLTestTexture Export)

ADD_TEST(TextureGlutTest GlutTestTexture)
ADD_TEST(TestTextureMyGL MyGLTestTexture)
