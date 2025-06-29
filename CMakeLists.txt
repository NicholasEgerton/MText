cmake_minimum_required(VERSION 3.28)
project(MText LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)

set(SOURCES
    src/Source.cpp
 "include/MText.h" "src/MText.cpp" "include/Errors.h" "src/Errors.cpp")

add_executable(MText ${SOURCES} "include/Errors.h")
target_compile_features(MText PRIVATE cxx_std_17)
target_link_libraries(MText PRIVATE SFML::Graphics)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "MText")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)