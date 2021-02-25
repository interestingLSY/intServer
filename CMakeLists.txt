cmake_minimum_required(VERSION 3.16) # TODO Modify this!

project(
	intServer
	DESCRIPTION "A High Performance Minecraft Server"
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include (cmake/flags.cmake)

include_directories(src/3rdparty/libnbtplusplus/include)
include_directories(src/3rdparty/json/single_include/nlohmann)
add_subdirectory(src/3rdparty/libnbtplusplus)

set(HEADERS
	src/base/common.hpp
	src/base/io/log.hpp
	src/base/network/packetReader.hpp
	src/base/network/packetWriter.hpp
	src/base/network/networkMain.hpp
	src/world/world.hpp
   )

set(SOURCES
	src/intServer.cpp
   )

include_directories(src)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} nbt++)
