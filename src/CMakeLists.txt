cmake_minimum_required(VERSION 3.12)

add_executable("${CMAKE_PROJECT_NAME}" main.cpp)

set_target_properties(
    "${CMAKE_PROJECT_NAME}"
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
    TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME DESTINATION bin
        COMPONENT prog
)
