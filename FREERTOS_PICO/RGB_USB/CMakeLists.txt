cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(/home/evg/SOFT/Github/PICO/FREERTOS_PICO/pico-sdk/external/pico_sdk_import.cmake)

project(RGB_USB C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CFG_TUSB_MCU OPT_MCU_RP2040)
include_directories(${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/hw)
include_directories(${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src)
#include_directories(${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/device)


# Initialize the SDK
pico_sdk_init()

add_executable(rgb_usb
    main.c
    usb_descriptors.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/hw/bsp/rp2040/family.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/class/cdc/cdc_device.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/device/usbd.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/device/usbd_control.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/common/tusb_fifo.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/tusb.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.c
    ${CMAKE_SOURCE_DIR}/../pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040/hcd_rp2040.c
#    rgb_usb.c
)

target_include_directories(rgb_usb PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# pull in common dependencies
target_link_libraries(rgb_usb pico_stdlib )

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(rgb_usb)

