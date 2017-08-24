cmake_minimum_required(VERSION 3.7)
project(mint64)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES)

add_custom_target(make-clean COMMAND make clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_target(make-utility COMMAND make -C 04.Utility WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-clean)
add_custom_target(make-bootloader COMMAND make -C 00.BootLoader WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-utility)
add_custom_target(make-kernel32 COMMAND make -C 01.Kernel32 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-bootloader)
add_custom_target(make-kernel64 COMMAND make -C 02.Kernel64 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-kernel32)
add_custom_target(make-Disk.img COMMAND make Disk.img WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-kernel64)
add_custom_target(run COMMAND ./qemu-x86_64.bat WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-Disk.img)

add_executable(mint64 build/Build.c)