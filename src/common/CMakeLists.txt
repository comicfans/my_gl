INCLUDE_DIRECTORIES(../soft_impl)

SUBDIRS(test)

ADD_LIBRARY(Vec4 Vec4.cpp)

ADD_LIBRARY(Matrix Matrix.cpp MatrixStack.cpp)

ADD_LIBRARY(Vec4Manager Vec4Manager.cpp)


ADD_LIBRARY(Vec4Provider 
     Vec4Provider.cpp
     UniqueVec4Provider.cpp 
     ArrayVec4Provider.cpp
     BufferObjectVec4Provider.cpp
     ClientArrayVec4Provider.cpp
     )
TARGET_LINK_LIBRARIES(Vec4Provider Vec4)

TARGET_LINK_LIBRARIES(Vec4Manager Vec4Provider)

ADD_LIBRARY(Context Context.cpp)

ADD_LIBRARY(Common UntypedArray.cpp PixelUnpacker.cpp )

