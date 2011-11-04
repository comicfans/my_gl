INCLUDE_DIRECTORIES(../)

ADD_LIBRARY(Shader 
     VertexShader.cpp
     NoLightVertexShader.cpp
     LightVertexShader.cpp
     FragmentShader.cpp
     MatrixParam.cpp
     SimpleFragmentShader.cpp
     VertexAttributeBuffer.cpp
     FragmentAttributeBuffer.cpp)

SUBDIRS(test)
