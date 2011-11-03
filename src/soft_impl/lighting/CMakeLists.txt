SUBDIRS(test)

ADD_LIBRARY(Lighting MaterialParam.cpp LightSourceParam.cpp GroupLightingParam.cpp)

TARGET_LINK_LIBRARIES(Lighting Matrix)
