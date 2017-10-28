cmake_minimum_required (VERSION 3.1)
project(cbor11)
set(CMAKE_CXX_STANDARD 11)
add_library(cbor11 src/cbor11.cpp)
target_include_directories(cbor11 PRIVATE include)

add_executable(cbor11-tests tst/cbor11_tests.cpp)
target_link_libraries(cbor11-tests cbor11)
target_include_directories(cbor11-tests PRIVATE include)
if(ENABLE_ASAN)
    target_compile_options(cbor11 PUBLIC "-fsanitize=address,undefined")
    target_link_libraries(cbor11 INTERFACE "-fsanitize=address,undefined")
endif()

include(CTest)
enable_testing()
add_test(cbor11 cbor11-tests)

install (FILES cbor11.h DESTINATION "include/cbor11")
install (
    TARGETS cbor11
    EXPORT "cbor11-config"
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library
    )

export(TARGETS cbor11 FILE "cbor11-config.cmake")
install(EXPORT cbor11-config DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cbor11/cmake/")

