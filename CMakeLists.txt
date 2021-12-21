cmake_minimum_required(VERSION 3.20)

project(newton-method VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

string(TIMESTAMP BUILD_DATE "%Y%m%d")
string(TIMESTAMP BUILD_TIME "%H%M%S")

configure_file(configure/config.txt resources/config.txt)

add_executable(
        newton-method
        src/main.cpp
        src/DataVector.cpp
        src/Equation.cpp
)

add_custom_command(
        TARGET newton-method POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:newton-method>/resources
)

enable_testing()

add_test(NAME OutputTest COMMAND newton-method)
set_tests_properties(
        OutputTest
        PROPERTIES PASS_REGULAR_EXPRESSION "resources outpt"
)

add_test(NAME VersionTest COMMAND newton-method -v)
set_tests_properties(
        VersionTest
        PROPERTIES PASS_REGULAR_EXPRESSION "Version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)
