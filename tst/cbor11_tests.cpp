#include "cbor11.h"
#include <iostream>

int test_incomplete_data()
{
    unsigned char data[] = {0x18, 0xFF, 0xFF};
    cbor::binary bin{std::begin(data), std::end(data)};
    auto res = cbor::decode(bin);
    return cbor::validate(res) | !res.is_undefined();
}

int main(int argc, char **argv)
{
    // Create complicated CBOR with simple code thanks to C++11
    cbor item = cbor::array {
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
    item = cbor::decode(data);

    int ret = 0;
    ret |= item != item;
    ret |= test_incomplete_data();
    return ret;
}
