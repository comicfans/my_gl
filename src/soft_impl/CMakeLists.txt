SUBDIRS(attribute_manager object test shader lighting pipeline image_compare)



ADD_LIBRARY(SDLPixelDrawer SDLPixelDrawer.cpp PixelDrawer.cpp)
TARGET_LINK_LIBRARIES(SDLPixelDrawer ${SDL_LIBRARY} )

ADD_LIBRARY(SoftImpl 
     DepthRange.cpp
     SoftContext.cpp
     ElementIndexManager.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl 
     Export
     SDLPixelDrawer
     Object 
     AttributeVertexManagers 
     Context
     Matrix
     Shader
     Lighting
     Pipeline )

