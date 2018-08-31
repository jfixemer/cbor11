add_library(cbor11 cbor11.cpp)
target_include_directories(cbor11 PRIVATE ${CMAKE_SOURCE_DIR}/include)

install (
    TARGETS cbor11
    EXPORT "cbor11-config"
    ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT library
    )