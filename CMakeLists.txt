cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0.0)

# Creating an interface library called tutorial_compiler_flags
# add_library(manipulator_compiler_flags INTERFACE)
# target_compile_features(manipulator_compiler_flags INTERFACE cxx_std_17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Put executable file in folder build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# configure a header file to pass some of the CMake settings to the source code
configure_file(HeaderConfig.h.in HeaderConfig.h)

# add the custom library
add_subdirectory(KINEMATICS)
add_subdirectory(DRIVER)
add_subdirectory(MCU)
add_subdirectory(MOTOR)
add_subdirectory(SERIAL)
add_subdirectory(MANIPULATOR)

# add include directories for all project
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/driver
    ${CMAKE_SOURCE_DIR}/kinematics
    ${CMAKE_SOURCE_DIR}/mcu
    ${CMAKE_SOURCE_DIR}/motor
    ${CMAKE_SOURCE_DIR}/serial
    ${CMAKE_SOURCE_DIR}/manipulator
)

# add the executable
add_executable(Tutorial src/main.cpp)

# link the executable with custom library
target_link_libraries(Tutorial PUBLIC KINEMATICS     )
target_link_libraries(Tutorial PUBLIC DRIVER         )
target_link_libraries(Tutorial PUBLIC MCU            )
target_link_libraries(Tutorial PUBLIC MOTOR          )
target_link_libraries(Tutorial PUBLIC SERIAL         )
target_link_libraries(Tutorial PUBLIC MANIPULATOR    )

# add the binary tree to the search path for include files
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
