# CMake minimum required version
cmake_minimum_required(VERSION 3.5)

# Top level project
project(Converter)

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
