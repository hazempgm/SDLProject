# CMakeList.txt : CMake project for SDLProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(HEADER_PATH include)
set(SOURCE_PATH src)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_BUILD_TYPE Release)

set(PROGRAM sample)

file(GLOB_RECURSE MODULE_SOURCE ${SOURCE_PATH}/*.cpp)

# Add source to this project's executable.
add_executable (${PROGRAM} ${MODULE_SOURCE})

target_include_directories(${PROGRAM} PUBLIC ${HEADER_PATH})

set_target_properties(${PROGRAM} PROPERTIES LINKER_LANGUAGE CXX)

set(BUILD FALSE
	CACHE BOOL
	"Creates a second executable."
	)

if(${BUILD})
	add_executable(
		sample2 ${MODULE_SOURCE} ${MODULE_HEADER}
	)
	set_target_properties(sample2 PROPERTIES LINKER_LANGUAGE CXX)
endif()



# TODO: Add tests and install targets if needed.
