cmake_minimum_required(VERSION 3.15)
project(shift_array)

set(CMAKE_CXX_STANDARD 17)

#[[
if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    else()
        # nothing special for gcc at the moment
    endif()
endif()
]]

add_compile_options("-Wall" "-Wextra" "$<$<CONFIG:RELEASE>:-O3>")

add_executable(shift_array main.cpp)