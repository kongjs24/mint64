cmake_minimum_required(VERSION 3.3)
project(mint64)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    00.BootLoader/BootLoader.asm
    00.BootLoader/makefile
    01.Kernel32/Source/Main.c
    01.Kernel32/Source/ModeSwitch.h
    01.Kernel32/Source/Page.c
    01.Kernel32/Source/Page.h
    01.Kernel32/Source/Types.h
    01.Kernel32/elf_i386_mac.x
    01.Kernel32/makefile
    02.Kernel64/Source/AssemblyUtility.h
    02.Kernel64/Source/Console.c
    02.Kernel64/Source/Console.h
    02.Kernel64/Source/ConsoleShell.c
    02.Kernel64/Source/ConsoleShell.h
    02.Kernel64/Source/Descriptor.c
    02.Kernel64/Source/Descriptor.h
    02.Kernel64/Source/InterruptHandler.c
    02.Kernel64/Source/InterruptHandler.h
    02.Kernel64/Source/ISR.h
    02.Kernel64/Source/Keyboard.c
    02.Kernel64/Source/Keyboard.h
    02.Kernel64/Source/List.c
    02.Kernel64/Source/List.h
    02.Kernel64/Source/Main.c
    02.Kernel64/Source/PIC.c
    02.Kernel64/Source/PIC.h
    02.Kernel64/Source/PIT.c
    02.Kernel64/Source/PIT.h
    02.Kernel64/Source/Queue.c
    02.Kernel64/Source/Queue.h
    02.Kernel64/Source/RTC.c
    02.Kernel64/Source/RTC.h
    02.Kernel64/Source/Task.c
    02.Kernel64/Source/Task.h
    02.Kernel64/Source/Types.h
    02.Kernel64/Source/Utility.c
    02.Kernel64/Source/Utility.h
    02.Kernel64/elf_x86_64_mac.x
    02.Kernel64/makefile
    04.Utility/00.ImageMaker/ImageMaker.c
    04.Utility/00.ImageMaker/makefile
    04.Utility/makefile
    mac.command
    makefile)

add_custom_target(make-clean COMMAND make clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_target(make-bootloader COMMAND make -C 00.BootLoader WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-utility)
add_custom_target(make-kernel32 COMMAND make -C 01.Kernel32 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-bootloader)
add_custom_target(make-kernel64 COMMAND make -C 02.Kernel64 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-kernel32)
add_custom_target(make-Disk.img COMMAND make Disk.img WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-kernel64)
add_custom_target(make-utility COMMAND make -C 04.Utility WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-clean)
add_custom_target(run COMMAND ./mac.command WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS make-Disk.img)

add_executable(mint64 Main.c)
