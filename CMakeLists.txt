cmake_minimum_required(VERSION 3.15)
project (crc32csum)

option(BUILD_STATIC_EXECUTABLE "Build static executable. Only valid on Linux" OFF)

include_directories(${PROJECT_SOURCE_DIR}/crc32c-hw)


set(CMAKE_BUILD_TYPE Release)

if (WIN32)
    add_library(crc32c SHARED IMPORTED GLOBAL)
    set_target_properties(crc32c PROPERTIES
        IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/crc32c-hw/x64/Release/crc32c64.dll"
        IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/crc32c-hw/x64/Release/crc32c64.lib"
    )
    target_include_directories(crc32c INTERFACE "${PROJECT_SOURCE_DIR}/crc32c-hw")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

    set(PROJECT_LINK_LIBS libcrc32c.a)
    link_directories(crc32c-hw)
	#link_libraries("-static")
endif()

set(SOURCES src/crc32csum.h src/crc32csum.cpp)
# set(TEST_SOURCES src/crc32csum.h src/crc32csum-test.cpp)

add_executable(crc32csum ${SOURCES})
# add_executable(crc32csum-test ${TEST_SOURCES})

if (WIN32)
    target_link_libraries(crc32csum crc32c)
    # target_link_libraries(crc32csum-test crc32c)

    # Restore nuget packages https://docs.microsoft.com/en-us/nuget/consume-packages/package-restore#restore-using-msbuild
    # add_custom_command(TARGET crc32csum PRE_BUILD
    #    COMMAND ${CMAKE_MAKE_PROGRAM} crc32c.sln -t:restore WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/crc32c-hw)
    add_custom_command(TARGET crc32csum PRE_BUILD
        COMMAND ${CMAKE_MAKE_PROGRAM} crc32c.sln /p:Configuration=Release /p:Platform=x64 /target:crc32c WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/crc32c-hw)
    add_custom_command(TARGET crc32csum POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:crc32c> $<TARGET_FILE_DIR:crc32csum>/)

    message(STATUS "Msbuild.exe location: ${CMAKE_MAKE_PROGRAM}")
elseif(APPLE)
    target_link_libraries(crc32csum ${PROJECT_LINK_LIBS})
    # target_link_libraries(crc32csum-test ${PROJECT_LINK_LIBS})
    if(BUILD_STATIC_EXECUTABLE)
        message(STATUS "Will build static executable")
    endif()

    add_custom_command(TARGET crc32csum PRE_BUILD
        COMMAND ${CMAKE_MAKE_PROGRAM} build WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/crc32c-hw)
else()
    if(BUILD_STATIC_EXECUTABLE)
        message(STATUS "Will build static executable")
        target_link_libraries(crc32csum ${PROJECT_LINK_LIBS} -static)
    else()
        target_link_libraries(crc32csum ${PROJECT_LINK_LIBS})
    endif()

    # target_link_libraries(crc32csum-test ${PROJECT_LINK_LIBS})

    add_custom_command(TARGET crc32csum PRE_BUILD
        COMMAND ${CMAKE_MAKE_PROGRAM} build WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/crc32c-hw)
endif()
