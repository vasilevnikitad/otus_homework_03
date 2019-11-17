cmake_minimum_required(VERSION 3.12)

project(ip_filter_pkg
        VERSION ${PROJECT_VERSION})

set(CPACK_GENERATOR                       DEB)
set(CPACK_DEB_COMPONENT_INSTALL           ON)
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS        ON)
set(CPACK_DEBIAN_PROG_PACKAGE_DEPENDS     ip_filter-lib)

set(CPACK_PACKAGE_VERSION       "${PROJECT_VERSION}")
set(CPACK_PACKAGE_ARCHITECTURE  "amd64")
set(CPACK_PACKAGE_CONTACT       vasilevnikitad@gmail.com)

include(CPack)
