cmake_minimum_required(VERSION 3.13)

# This file needs to be included before calling `project`.
include(cmake/UniversalAppleBuild.cmake)

project (crc32csum
    VERSION "2.0.0"
    DESCRIPTION "Simple crc32c checksum utility"
    HOMEPAGE_URL "https://github.com/dogukancagatay/crc32csum.git"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Doğukan Çağatay") #required
set(CPACK_PACKAGE_CONTACT "dcagatay@gmail.com") #required
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple crc32c checksum utility"
    CACHE STRING "Checksum utility for computing crc32c checksums."
)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

# set(CRC32C_BUILD_TESTS 0)
set(CRC32C_BUILD_BENCHMARKS 0)
add_subdirectory(crc32c)
include_directories(${CMAKE_SOURCE_DIR}/crc32c/include)

set(SOURCES src/crc32csum.cpp src/crc32csum.h)
add_executable(crc32csum ${SOURCES})

set(TEST_SOURCES src/crc32csum-test.cpp src/crc32csum.h)
add_executable(crc32csum-test ${TEST_SOURCES})

# TODO: Fix Windows build
if (WIN32)
    add_library(crc32c SHARED IMPORTED GLOBAL)
    set_target_properties(crc32c PROPERTIES
        IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/crc32c/x64/Release/crc32c64.dll"
        IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/crc32c/x64/Release/crc32c64.lib"
    )
    target_include_directories(crc32c INTERFACE "${PROJECT_SOURCE_DIR}/crc32c")
    target_link_libraries(crc32csum crc32c)

    add_custom_command(TARGET crc32csum PRE_BUILD
        COMMAND ${CMAKE_MAKE_PROGRAM} crc32c.sln /p:Configuration=Release /p:Platform=x64 /target:crc32c WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/crc32c-hw)
    add_custom_command(TARGET crc32csum POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:crc32c> $<TARGET_FILE_DIR:crc32csum>/)

    message(STATUS "Msbuild.exe location: ${CMAKE_MAKE_PROGRAM}")
# elseif(APPLE)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
#     target_link_libraries(crc32csum crc32c)
#     target_link_libraries(crc32csum-test crc32c)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    target_link_libraries(crc32csum crc32c)
    target_link_libraries(crc32csum-test crc32c)

    enable_testing()
    add_test(NAME crc32csum-test COMMAND $<TARGET_FILE:crc32csum-test>)
endif()

include(GNUInstallDirs)

install(TARGETS crc32csum
    COMPONENT crc32csum
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CPack)
