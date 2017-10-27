#include "cbor11.h"
#include <iostream>

int main(int argc, char **argv)
{
    // Create complicated CBOR with simple code thanks to C++11
    cbor item = cbor::array {
        12,
            -12,
            "Hello",
            cbor::binary {0xff, 0xff},
            cbor::array {"Alice", "Bob", "Eve"},
            cbor::map {
                {"CH", "Switzerland"},
                {"DK", "Denmark"},
                {"JP", "Japan"}
            },
            cbor::simple (0),
            false,
            nullptr,
            cbor::undefined,
            1.2
    };

    // Convert to diagnostic notation for easy debugging
    std::cout << cbor::debug (item) << std::endl;

    // Encode
    cbor::binary data = cbor::encode (item);

    // Decode (if invalid data is given cbor::undefined is returned)
    item = cbor::decode (data);
    return item != item;
}
