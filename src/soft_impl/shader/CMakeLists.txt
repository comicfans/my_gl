INCLUDE_DIRECTORIES(../)

ADD_LIBRARY(Shader 
     VertexShader.cpp
     NoLightVertexShader.cpp
     FragmentShader.cpp
     SimpleFragmentShader.cpp
     VertexAttributeBuffer.cpp
     FragmentAttributeBuffer.cpp)
