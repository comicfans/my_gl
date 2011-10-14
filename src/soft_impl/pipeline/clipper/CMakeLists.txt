INCLUDE_DIRECTORIES(../../)

ADD_LIBRARY(Clipper Clipper.cpp PointClipper.cpp LineClipper.cpp)
SUBDIRS(test)
