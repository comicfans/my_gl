SUBDIRS(attribute_manager object test)


ADD_LIBRARY(SoftImpl 
     SoftContext.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl 
     Object 
     AttributeVertexManagers 
     Context
     Matrix)
