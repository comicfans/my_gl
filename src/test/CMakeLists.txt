INCLUDE_DIRECTORIES(
     ${GLUT_INCLUDE_DIR} 
     ${GLEW_INCLUDE_PATH}
     ./)
    
ADD_LIBRARY(GlutInit GlutInit.cpp)


SUBDIRS(test_array_buffer_object
     test_client_vertex_pointer
     test_rotate test_scale
     test_draw_elements
     test_perspective_project
     test_cull_face
     test_lighting
     test_texture)
