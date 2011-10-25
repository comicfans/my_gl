SUBDIRS(attribute_manager object test shader pipeline)

INCLUDE_DIRECTORIES(.)
ADD_LIBRARY(SoftImpl 
     SoftContext.cpp
     ElementIndexManager.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl 
     Object 
     AttributeVertexManagers 
     Context
     Matrix
     Shader
     Pipeline)
