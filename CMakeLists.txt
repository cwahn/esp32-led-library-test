cmake_minimum_required(VERSION 3.5.0)
project(Esp32LedBlinker VERSION 0.1.0 LANGUAGES C CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# temp C++ 14 for auto lambda
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include("cmake/CPM.cmake")

CPMAddPackage(
    NAME efp
    VERSION 0.1.0-rc.6
    URL "https://github.com/cwahn/efp/archive/refs/tags/v0.1.0-rc.6.tar.gz"
)

# If this is the top-level CMakeLists.txt
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(tests)
    add_subdirectory(examples)
endif()

# Reference: https://github.com/espressif/esp-idf/blob/v5.2.3/examples/build_system/cmake/idf_as_lib/CMakeLists.txt
set(targets "esp32" "esp32s2" "esp32s3" "esp32c3" "esp32c2" "esp32c6" "esp32h2" "esp32p4")

if("${TARGET}" IN_LIST targets)
    # Include for ESP-IDF build system functions
    include($ENV{IDF_PATH}/tools/cmake/idf.cmake)

    # Create idf::{target} and idf::freertos static libraries
    idf_build_process("${TARGET}"
        COMPONENTS freertos esptool_py
        # SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
        BUILD_DIR ${CMAKE_BINARY_DIR})

    file(GLOB LIB_SRC
        src/lib.cpp
    )

    add_library(esp32-led-blinker STATIC ${LIB_SRC})

    target_include_directories(esp32-led-blinker
        PUBLIC
        "./include")

    target_link_libraries(esp32-led-blinker
        PUBLIC
        efp
    )

    idf_build_component(esp32-led-blinker)

else()
    if(NOT TARGET)
        message(FATAL_ERROR "TARGET not set")
    else()
        message(FATAL_ERROR "Unknown target ${TARGET}")
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

