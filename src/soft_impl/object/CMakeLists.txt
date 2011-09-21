INCLUDE_DIRECTORIES(../)

ADD_LIBRARY(Object 
     BufferObject.cpp 
     ArrayBufferObject.cpp
     ObjectNameManager.cpp
     PixelObject.cpp
     ArrayBufferObjectManager.cpp
     )
TARGET_LINK_LIBRARIES(Object Common)
