# CMAKE SETTINGS
cmake_minimum_required(VERSION 3.6)
project(cglw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# PROJECT CONFIG/SETUP
file(GLOB_RECURSE HEADER_FILES "src/*.h" "src/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# DEPENDENCIES

## glad
set(GLAD_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/glad")
set(GLAD_SOURCES_DIR "${GLAD_LIB_DIR}/")
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        7acc116b06f40508b82fd90fc58d181be7e65452
        SOURCE_DIR     "${GLAD_LIB_DIR}"
        PATCH_COMMAND
        ${CMAKE_COMMAND} -E copy "${GLAD_LIB_DIR}/cmake/CMakeLists.txt" "${GLAD_LIB_DIR}/CMakeLists.txt" &&
        ${CMAKE_COMMAND} -E copy "${GLAD_LIB_DIR}/cmake/GladConfig.cmake" "${GLAD_LIB_DIR}/GladConfig.cmake"
)
FetchContent_MakeAvailable(glad)

## glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm.git
        GIT_TAG 	    2d4c4b4dd31fde06cfffad7915c2b3006402322f
        SOURCE_DIR	    "${PROJECT_SOURCE_DIR}/lib/glm"
)
FetchContent_MakeAvailable(glm)

# Library

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME}
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# link
glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE API gl:core=4.6)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glad_gl_core_46
)
target_link_libraries(${PROJECT_NAME} PUBLIC
        glm
)