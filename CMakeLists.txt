cmake_minimum_required(VERSION 2.8)

# Project Name
PROJECT(motor)

if (NOT APPLE)
    if (WIN32)
        set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
        include_directories(
                ${TOOLKITS_FOLDER}/glew
                ${TOOLKITS_FOLDER}/glut
                ${TOOLKITS_FOLDER}/devil)
        link_directories(
                ${TOOLKITS_FOLDER}/glew
                ${TOOLKITS_FOLDER}/glut
                ${TOOLKITS_FOLDER}/devil)
    else(WIN32)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif(WIN32)
endif(NOT APPLE)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

	find_package(DevIL REQUIRED)
	link_libraries(${IL_LIBRARIES} )
	include_directories(ยง{IL_INCLUDE_DIR})

if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(${PROJECT_NAME} main.cpp engine.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
