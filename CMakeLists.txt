# CMake minimum required version
cmake_minimum_required(VERSION 3.21.0)

# Top level project
project(Converter)
#SET(CMAKE_GENERATOR_PLATFORM x64)

#set(CMAKE_EXE_LINKER_FLAGS "-Wl,-allow-multiple-definition -static-libgcc -static-libstdc++ -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")


#set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")



# Shared libraries
set(SHARED_LIBS
	Visualization
)

set(SUBPROJECTS
	${SHARED_LIBS}
)

# Library subprojects
foreach(SUBPROJECT ${SUBPROJECTS})
	# Add subproject
	add_subdirectory(${SUBPROJECT})
endforeach(SUBPROJECT)
