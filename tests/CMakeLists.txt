# set(targets "esp32" "esp32s2" "esp32s3" "esp32c3" "esp32c2" "esp32c6" "esp32h2" "esp32p4")

# if("${TARGET}" IN_LIST targets)
# include($ENV{IDF_PATH}/tools/cmake/idf.cmake)

# idf_build_process("${TARGET}"
# # COMPONENTS freertos esptool_py
# SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
# BUILD_DIR ${CMAKE_BINARY_DIR}
# )
# else()
# message(WARNING "Unknown target ${TARGET}, creating stubs for esp32 instead")
# # Create stubs for esp32 and freertos, stub::esp32 and stub::freertos
# add_subdirectory(stubs/esp32)
# add_subdirectory(stubs/freertos)
# add_subdirectory(stubs/spi_flash)
# endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(elf_file ${CMAKE_PROJECT_NAME}.elf)
# add_executable(${elf_file} main.c)

# # Link the static libraries to the executable
# if("${TARGET}" IN_LIST targets)
# target_link_libraries(${elf_file} idf::freertos idf::spi_flash)
# # Attach additional targets to the executable file for flashing,
# # linker script generation, partition_table generation, etc.
# idf_build_executable(${elf_file})
# else()
# target_link_libraries(${elf_file} stub::esp32 stub::freertos stub::spi_flash)
# endif()

add_executable(esp32-led-blinker-test "test.cpp")

# Set TARGET for this executable target
target_compile_definitions(esp32-led-blinker-test PRIVATE TARGET="esp32")
target_link_libraries(esp32-led-blinker-test PRIVATE esp32-led-blinker)

idf_build_process(esp32-led-blinker-test
    SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
    BUILD_DIR ${CMAKE_BINARY_DIR}
)
