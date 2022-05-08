cmake_minimum_required(VERSION 3.20)

project(dasimb)

set(sources
	RandInt.cpp
	Graph.cpp
	EntitySet.cpp
	EntityBase.cpp
	Entity.cpp
	Topology.cpp
	Simulator.cpp
	main.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

set(libs )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(libs ${libs} )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(libs ${libs} )
endif()

set(MYLIBS)
foreach(lib ${libs})
	set(the_lib ${lib}-NOTFOUND)
	find_library(the_lib ${lib} PATHS "/opt/local/lib" "$ENV{COLIBRY}/lib")
	set(MYLIBS ${MYLIBS} ${the_lib})
endforeach(lib)

# INCLUDES + COMPILER OPTIONS
include_directories("/opt/local/include")
# add_compile_options(_______________)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} ${MYLIBS})
