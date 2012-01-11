INCLUDE_DIRECTORIES(../soft_impl)

SUBDIRS(test)

ADD_LIBRARY(Vec Vec.cpp)

ADD_LIBRARY(Matrix Matrix.cpp MatrixStack.cpp)

ADD_LIBRARY(Vec4Manager Vec4Manager.cpp)


ADD_LIBRARY(Vec4Provider 
     Vec4Provider.cpp
     UniqueVec4Provider.cpp 
     ArrayVec4Provider.cpp
     BufferObjectVec4Provider.cpp
     ClientArrayVec4Provider.cpp
     )

TARGET_LINK_LIBRARIES(Vec4Provider Vec)

TARGET_LINK_LIBRARIES(Vec4Manager Vec4Provider)

ADD_LIBRARY(Context Context.cpp)

ADD_LIBRARY(Common UntypedArray.cpp PixelUnpacker.cpp )

FIND_LIBRARY(OpenGL REQUIRED)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

ADD_LIBRARY(Export Export.cpp)

TARGET_LINK_LIBRARIES(Export SoftImpl OpenCLImpl)
