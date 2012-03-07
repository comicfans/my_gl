INCLUDE_DIRECTORIES(../../../3rd ${OPENCL_INCLUDE_DIR})
ADD_EXECUTABLE(ImageComparatorCmd ImageComparatorCmd.cpp ImageComparator.cpp Image.cpp)

TARGET_LINK_LIBRARIES(ImageComparatorCmd EasyBMP SoftImageComparator OpenCLImageComparator)

