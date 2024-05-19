cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(/home/evg/SOFT/Github/PICO/FREERTOS_PICO/pico-sdk/external/pico_sdk_import.cmake)

project(RGB_UART C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(rgb_uart rgb_uart.c)

target_include_directories(rgb_uart PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# pull in common dependencies
target_link_libraries(rgb_uart pico_stdlib )

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(rgb_uart)

