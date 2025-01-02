cmake_minimum_required(VERSION 3.29)
project(Game)
set(APPLICATION_LIBRARY GameLib)

set(CMAKE_CXX_STANDARD 17)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp
        GameApp.cpp
        GameApp.h
        pch.h
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SpartysBoots.ico
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Define a variable containing a list of resource files (only on Windows)
if (WIN32)
    set(RESOURCE_FILES SpartysBoots.rc)
endif ()

# Rename the executable to Game to match the project name
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

add_definitions(-D_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING)

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

add_subdirectory(Tests)

if (APPLE)
    # When building for MacOS, also copy files into the bundle resources
    set(RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/Game.app/Contents/Resources)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/ DESTINATION ${RESOURCE_DIR}/images/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/ DESTINATION ${RESOURCE_DIR}/levels/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SpartysBoots.ico DESTINATION ${RESOURCE_DIR}/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SpartysBoots.icns DESTINATION ${RESOURCE_DIR}/)
endif ()