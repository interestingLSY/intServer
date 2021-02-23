set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "release")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "debug")
	add_definitions(/DAPP_DEBUG)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wnarrowing")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast ")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wnarrowing -pthread")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -pthread")
else()
	message(FATAL_ERROR "Only GNU compilers are supported. QAQ")
endif()
