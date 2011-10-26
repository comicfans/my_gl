SUBDIRS(attribute_manager object test shader pipeline)

INCLUDE_DIRECTORIES(. ${SDL_INCLUDE_DIR})
ADD_LIBRARY(SoftImpl 
     SoftContext.cpp
     ElementIndexManager.cpp
     PixelDrawer.cpp
     SDLPixelDrawer.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl 
     Object 
     AttributeVertexManagers 
     Context
     Matrix
     Shader
     Pipeline ${SDL_LIBRARY})

