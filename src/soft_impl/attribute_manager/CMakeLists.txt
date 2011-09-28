INCLUDE_DIRECTORIES(../)

ADD_LIBRARY(AttributeVertexManagers 
     TwoSourceVec4Manager.cpp
     NormalManager.cpp  
     ColorManager.cpp
     VertexManager.cpp
     TexCoordManager.cpp)

TARGET_LINK_LIBRARIES(AttributeVertexManagers Vec4Manager )
