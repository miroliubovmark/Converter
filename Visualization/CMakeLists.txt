cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Visualization)
project(${PROJECT_NAME})
#set(TEST_PROJECT_NAME VisualizationTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_AUTOMOC ON)
add_compile_options(-fPIC)

set(HEADER_FILES
	UBaseTypes.h
	VisualizationStable.h

	CDlgWarning.h
	CLineEdit.h
	CMainWindow.h
	CConverter.h
)

set(SOURCE_FILES
	CDlgWarning.cpp
	CLineEdit.cpp
	CMainWindow.cpp
	CConverter.cpp
)

# Add QT libraries
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Qt5Core_INCLUDES})
include_directories(${Qt5Widgets_INCLUDES})


# Add sources to the test project
#set(${TEST_PROJECT_NAME}_SOURCES
#	UToolsTest.cpp
#)

# Add libraries to the test project
#set(${TEST_PROJECT_NAME}_LIBS
#	Visualization
#)


add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${Qt5Core_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Qt5::Core)

add_executable(main main.cpp)

target_link_libraries(main ${PROJECT_NAME})

#add_executable(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME}.cpp)

#target_link_libraries(${TEST_PROJECT_NAME} Visualization)


