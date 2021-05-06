# CMakeList.txt : CMake project for SDLProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(HEADER_PATH include)
set(SOURCE_PATH src)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_BUILD_TYPE Release)

add_link_options(-lSDL2 -lSDL2_image -lpthread)
add_compile_options(-Ofast -Wall -Wextra)

include_directories(${HEADER_PATH})

set(PROGRAM sample)

file(GLOB_RECURSE MODULE_SOURCE ${SOURCE_PATH}/*.cpp)

# Add source to this project's executable.
add_executable (${PROGRAM} ${MODULE_SOURCE})

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
