SUBDIRS(attribute_manager object test shader pipeline)


ADD_LIBRARY(SoftImpl 
     SoftContext.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl 
     Object 
     AttributeVertexManagers 
     Context
     Matrix
     Shader)
