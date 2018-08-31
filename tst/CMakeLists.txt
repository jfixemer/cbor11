
include(CTest)

add_executable(cbor11-tests cbor11_tests.cpp)
target_link_libraries(cbor11-tests cbor11)

if(CBOR11_BUILD_ASAN)
    target_compile_options(cbor11 PUBLIC "-fsanitize=address,undefined")
    target_link_libraries(cbor11 INTERFACE "-fsanitize=address,undefined")
endif()

add_test(incomplete_data cbor11-tests "test_incomplete_data")
add_test(complex cbor11-tests "serialize_deserialize_complex_structure")
