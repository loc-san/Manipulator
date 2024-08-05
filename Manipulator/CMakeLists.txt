add_library(MANIPULATOR manipulator.cpp)

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

# State that anybody linking to MathFunctions needs to include the current source directory, 
# while MathFunctions itself doesn't.
# Hint: Use target_include_directories with the INTERFACE keyword
target_include_directories(MANIPULATOR INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})