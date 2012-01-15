SET(TEST_RUNNING_DIR ${CMAKE_BINARY_DIR}/test_running)

FILE(MAKE_DIRECTORY ${TEST_RUNNING_DIR})

MACRO (CHANGE_RUNNING_DIR TEST_NAME)
     SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES 
	  RUNTIME_OUTPUT_DIRECTORY ${TEST_RUNNING_DIR})
ENDMACRO()

MACRO(COPY_RUNTIME_FILE FILES)
     FILE(COPY ${FILES} DESTINATION ${TEST_RUNNING_DIR})
ENDMACRO()

MACRO (ADD_COMPARE_TEST TARGET_NAME)
     SET(MY_GL_NAME "MyGLTest${TARGET_NAME}")
     ADD_EXECUTABLE(${MY_GL_NAME} "${MY_GL_NAME}.cpp")
     CHANGE_RUNNING_DIR(${MY_GL_NAME})
     TARGET_LINK_LIBRARIES(${MY_GL_NAME} SoftImpl)
     SET(MY_GL_TEST_NAME "${TARGET_NAME}TestMyGL")
     ADD_TEST(${MY_GL_TEST_NAME} ${MY_GL_NAME})

     SET(OPENCL_NAME "OpenCLImplTest${TARGET_NAME}")
     ADD_EXECUTABLE(${OPENCL_NAME} "${OPENCL_NAME}.cpp")
     CHANGE_RUNNING_DIR(${OPENCL_NAME})
     TARGET_LINK_LIBRARIES("${OPENCL_NAME}" OpenCLImpl)
     SET(OPENCL_TEST_NAME "${TARGET_NAME}TestOpenCL")
     ADD_TEST(${OPENCL_TEST_NAME} ${OPENCL_NAME})


     SET(GLUT_NAME "GlutTest${TARGET_NAME}")
     ADD_EXECUTABLE(${GLUT_NAME} "${GLUT_NAME}.cpp")
     CHANGE_RUNNING_DIR(${GLUT_NAME})
     TARGET_LINK_LIBRARIES(${GLUT_NAME} 
	  GlutInit
	  ${GLEW_LIBRARY} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
     SET(GLUT_TEST_NAME "${TARGET_NAME}TestGlut")
     ADD_TEST(${GLUT_TEST_NAME} ${GLUT_NAME})
ENDMACRO()

