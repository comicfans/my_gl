SUBDIRS(attribute_manager object test shader lighting pipeline )

INCLUDE_DIRECTORIES(. ${SDL_INCLUDE_DIR})
ADD_LIBRARY(SoftImpl 
     SDLPixelDrawer.cpp
     DepthRange.cpp
     SoftContext.cpp
     ElementIndexManager.cpp
     PixelDrawer.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl 
     Object 
     AttributeVertexManagers 
     Context
     Matrix
     Shader
     Lighting
     Pipeline ${SDL_LIBRARY})

