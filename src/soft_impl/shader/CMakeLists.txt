INCLUDE_DIRECTORIES(../)

ADD_LIBRARY(VertexShader VertexShader.cpp 
     NoLightVertexShader.cpp
     LightVertexShader.cpp
     TwoSideLightVertexShader.cpp)


ADD_LIBRARY(FragmentShader FragmentShader.cpp
     SimpleFragmentShader.cpp TextureFragmentShader.cpp
     TextureLightFragmentShader.cpp)


ADD_LIBRARY(Shader 
     MatrixParam.cpp
     VertexAttributeBuffer.cpp
     FragmentAttributeBuffer.cpp)

TARGET_LINK_LIBRARIES(Shader VertexShader FragmentShader)

SUBDIRS(test)
