cmake_minimum_required (VERSION 3.19)
project("${CMAKE_PROJECT_NAME}")
include("$ENV{TOOLCHAIN_PATH}/CMakeLists.txt.in")

add_lib("lib${CMAKE_PROJECT_NAME}"
    "source/lib/meta"
    "source/lib/com"
    "source/lib/time"
)

add_unittest(lib${CMAKE_PROJECT_NAME})
