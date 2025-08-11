cmake_minimum_required(VERSION 3.6)
project(libs)

include(FetchContent)

add_library(${PROJECT_NAME} INTERFACE)

# DEPENDENCIES

## glad
set(GLAD_LIB_DIR "${PROJECT_SOURCE_DIR}/glad")
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
glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE API gl:core=4.6)

## glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm.git
        GIT_TAG 	    2d4c4b4dd31fde06cfffad7915c2b3006402322f
        SOURCE_DIR	    "${PROJECT_SOURCE_DIR}/glm"
)
FetchContent_MakeAvailable(glm)

# link
target_link_libraries(${PROJECT_NAME} INTERFACE
        glad_gl_core_46
        glm
)