#include "cbor11/cbor.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <limits>

using namespace cbor11;

bool test_incomplete_data()
{
    unsigned char data[] = {0x18, 0xFF, 0xFF};
    cbor::binary bin {std::begin(data), std::end(data)};
    auto res = cbor::decode(bin);
    return !cbor::validate(res) && res.is_undefined();
}

bool test_serialization_deserialization()
{
    // Test all half-floats.
    cbor::binary half{0xf9, 0x00, 0x00};
    int NaNcount = 2046;
    for (int i = 0; i < 65536; ++i) {
        half[1] = i>>8;
        half[2] = i;
        cbor dec = cbor::decode(half);
        if (dec.to_float() != dec.to_float()) {
            --NaNcount;
            continue;
        }
        cbor::binary half2 = cbor::encode(dec);
        if (half != half2) {
            std::cout << cbor::debug(half) << " to " << cbor::debug(dec) << " to " << cbor::debug(half2) << std::endl;
            return false;
        }
    }
    if (NaNcount) {
        std::cout << NaNcount << std::endl;
        return false;
    }
    // Test 100000 random floats.
    union {
        uint32_t n;
        float f;
    };
    n = 0;
    for (int i = 0; i < 100000; ++i) {
        n = 1664525*n + 1013904223;
        float g = cbor::decode(cbor::encode(f)).to_float();
        if (f != g && (f == f || g == g)) {
            std::cout << f << " to " << g << std::endl;
            return false;
        }
    }

    using nld = std::numeric_limits<double>;
    static_assert(nld::has_quiet_NaN, "Quiet NaN is not avaialble.");
    static_assert(nld::has_infinity, "Infinity is not avaialble.");

    const cbor item = cbor::array {
            cbor::array {24, 23, 12, -12, -24, -25},
            "Hello",
            cbor::binary {0xff, 0xff},
            cbor::map {
                {"CH", "Switzerland"},
                {"DK", "Denmark"},
                {"JP", "Japan"},
                {0, "zero"},
                {-1, "minus one"},
                {1, "one"},
                {-2, "minus two"}
            },
            cbor::array {"Alice", "Bob", 72, "Eve"},
            cbor::simple (0),
            false,
            nullptr,
            cbor::undefined,
            cbor::tagged(1024, -1.5),
            1000000000000000,
            nld::infinity(),
            nld::quiet_NaN(),
            1.2,
            1.2f
    };

    // Convert to diagnostic notation for easy debugging
    std::cout << cbor::debug (item) << std::endl;
    // Encode
    cbor::binary data = cbor::encode(item);
    std::cout << "<";
    for (uint8_t b : data) std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    std::cout << " >" << std::endl;
    // Decode (if invalid data is given cbor::undefined is returned)
    const auto output = cbor::decode(data);
    if (output != item) {
        std::cout << cbor::debug (output) << std::endl;
        return false;
    }
    return !output.is_undefined();
}

int main(int argc, char **argv)
{
    if(argc < 2)
        return -1;

    std::pair<std::string, bool(*)()> tests[] =
    {
        { "serialize_deserialize_complex_structure", &test_serialization_deserialization, },
        { "test_incomplete_data", &test_incomplete_data }
    };

    for(unsigned i = 0; i < sizeof(tests); i++) {
        if(tests[i].first == argv[1]) {
            return !tests[i].second();
        }
    }

    return -1;
}
