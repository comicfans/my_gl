INCLUDE_DIRECTORIES( .)

SUBDIRS(attribute_manager object)


ADD_LIBRARY(SoftImpl 
     SoftContext.cpp
     )

TARGET_LINK_LIBRARIES(SoftImpl Normal Object)
