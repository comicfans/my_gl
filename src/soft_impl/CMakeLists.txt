SUBDIRS(attribute_manager object test shader lighting pipeline )


INCLUDE_DIRECTORIES(. ${SDL_INCLUDE_DIR})


ADD_LIBRARY(SDLPixelDrawer SDLPixelDrawer.cpp PixelDrawer.cpp)
TARGET_LINK_LIBRARIES(SDLPixelDrawer ${SDL_LIBRARY} )

ADD_LIBRARY(SoftImpl 
     DepthRange.cpp
     SoftContext.cpp
     ElementIndexManager.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl 
     SDLPixelDrawer
     Object 
     AttributeVertexManagers 
     Context
     Matrix
     Shader
     Lighting
     Pipeline )

