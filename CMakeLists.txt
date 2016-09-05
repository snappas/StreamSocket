cmake_minimum_required(VERSION 3.6)
project(StreamSocket)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

set(SOURCE_FILES main.cpp Epoll_If.cxx Epoll_If.hxx Descriptor.hxx ServerDescriptor.cxx ServerDescriptor.hxx ClientDescriptor.cxx ClientDescriptor.hxx FileDescriptor.cxx FileDescriptor.hxx ExternalProcess.cxx ExternalProcess.hxx Server.cxx Server.hxx DataModel.cxx DataModel.hxx Descriptor.cxx)
add_executable(StreamSocket ${SOURCE_FILES})