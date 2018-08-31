cmake_minimum_required (VERSION 3.1)
set(CBOR11_VERSION 0.5.0)

include(GNUInstallDirs)
enable_testing()

project(cbor11 VERSION ${CBOR11_VERSION} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

option(CBOR11_BUILD_TESTS "Build cbor11 unittests." ON)
option(CBOR11_BUILD_ASAN "Build cbor11 unittests with address sanitizer (gcc/clang)" OFF)

IF(WIN32)
  if(MSVC)
     SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
  endif()
ENDIF()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)

if(CBOR11_BUILD_TESTS)
    add_subdirectory(tst)
endif()

install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/" 
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" )

export(TARGETS cbor11 FILE "cbor11-config.cmake")

install(EXPORT cbor11-config 
    NAMESPACE ${cmake_package_name}:: 
    DESTINATION  "${CMAKE_INSTALL_LIBDIR}/cmake/${cmake_package_name}")
