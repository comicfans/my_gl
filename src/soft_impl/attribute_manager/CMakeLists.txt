INCLUDE_DIRECTORIES(../)

ADD_LIBRARY(AttributeVertexManagers 
     TwoSourceVectorManager.cpp
     NormalManager.cpp  
     ColorManager.cpp
     VertexManager.cpp
     TexCoordManager.cpp)

TARGET_LINK_LIBRARIES(AttributeVertexManagers VectorManager )
