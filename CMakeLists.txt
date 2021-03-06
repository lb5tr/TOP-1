cmake_minimum_required (VERSION 3.1)
project (Tapedeck)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/src")

find_package(PkgConfig REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE TAPEDECK_SRC
  "src/*.cpp"
  "lib/*.cpp"
  "lib/*.c"
  "lib/*.cc"
)

add_executable(tapedeck ${TAPEDECK_SRC})

target_link_libraries(tapedeck pthread)
target_link_libraries(tapedeck dl)

include_directories("include/nanovg")
include_directories("include/nanocanvas")
include_directories("include")

function(target_add_lib name)
  pkg_check_modules(${name} REQUIRED ${name})
  target_link_libraries(tapedeck ${${name}_LIBRARIES})
  target_include_directories(tapedeck PUBLIC ${${name}_INCLUDE_DIRS})
  target_compile_options(tapedeck PUBLIC ${${name}_CFLAGS_OTHER})
endfunction(target_add_lib)

# DEPENDENCIES

target_add_lib(jack)
target_add_lib(glfw3)
target_add_lib(gl)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

# example usage
#enable_cxx_compiler_flag_if_supported("-Wall")
#enable_cxx_compiler_flag_if_supported("-Wextra")
#enable_cxx_compiler_flag_if_supported("-pedantic")

add_custom_command(TARGET tapedeck
  PRE_BUILD
  COMMAND "./compile-faust.sh"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
