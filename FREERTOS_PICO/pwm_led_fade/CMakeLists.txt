cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(/home/evg/SOFT/Github/PICO/FREERTOS_PICO/pico-sdk/external/pico_sdk_import.cmake)

project(pwm C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# pull in common dependencies
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_pwm
    )

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${PROJECT_NAME})

