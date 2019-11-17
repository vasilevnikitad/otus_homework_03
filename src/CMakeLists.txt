cmake_minimum_required(VERSION 3.12)

project(
    ip_filter_src
        LANGUAGES CXX
)

add_executable(ip_filter main.cpp)

set_target_properties(
    ip_filter
        PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED ON
            COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-Werror;"
            LINK_LIBRARIES "lib;${CMAKE_THREAD_LIBS_INIT}"
            BUILD_RPATH "${CMAKE_BINARY_DIR}/lib"
            INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
)

install(
    TARGETS ip_filter
        RUNTIME DESTINATION bin
        COMPONENT prog
)
