SUBDIRS(attribute_manager)
ADD_LIBRARY(SoftImpl BufferObject.cpp 
     TextureObject.cpp 
     ObjectNameManager.cpp)

TARGET_LINK_LIBRARIES(SoftImpl Normal)
