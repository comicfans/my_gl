
ADD_LIBRARY(CLRasterizer BatchRasterizer.cpp)

TARGET_LINK_LIBRARIES(CLRasterizer Rasterizer)

COPY_RUNTIME_FILE(BatchRasterizer.cl)
