INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rd/EasyBMP)

ADD_EXECUTABLE(GlutTestTexture GlutTestTexture.cpp)
TARGET_LINK_LIBRARIES(GlutTestTexture
     GlutInit
     ${GLUT_LIBRARY}
     ${GLEW_LIBRARY}
     ${OPENGL_LIBRARIES})

ADD_TEST(TextureGlutTest GlutTestTexture)
