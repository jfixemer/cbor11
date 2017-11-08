#include "cbor11.h"
#include <iostream>
#include <string>
#include <utility>

bool test_incomplete_data()
{
    unsigned char data[] = {0x18, 0xFF, 0xFF};
    cbor::binary bin {std::begin(data), std::end(data)};
    auto res = cbor::decode(bin);
    return !cbor::validate(res) && res.is_undefined();
}

bool test_serialization_deserialization()
{
    const cbor item = cbor::array {
            12,
            -12,
            "Hello",
            cbor::binary {0xff, 0xff},
            cbor::map {
                {"CH", "Switzerland"},
                {"DK", "Denmark"},
                {"JP", "Japan"}
            },
            cbor::array {"Alice", "Bob", 72, "Eve"},
            cbor::simple (0),
            false,
            nullptr,
            cbor::undefined,
            1.2
    };

    // Convert to diagnostic notation for easy debugging
    std::cout << cbor::debug (item) << std::endl;
    // Encode
    cbor::binary data = cbor::encode(item);
    // Decode (if invalid data is given cbor::undefined is returned)
    const auto output = cbor::decode(data);
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

    for(int i = 0; i < sizeof(tests); i++) {
        if(tests[i].first == argv[1]) {
            return !tests[i].second();
        }
    }

    return -1;
}
