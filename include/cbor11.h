// This is free and unencumbered software released into the public domain.
#pragma once
#if __cplusplus < 201103
#warning "To enable all features you must compile with -std=c++11"
#endif
#include <iostream>
#include <map>
#include <stdint.h>
#include <vector>
#if __cplusplus >= 201103
#include <initializer_list>
#endif

class cbor {
public:
    enum type_t {
        TYPE_UNSIGNED,
        TYPE_NEGATIVE,
        TYPE_BINARY,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_MAP,
        TYPE_TAGGED,
        TYPE_SIMPLE,
        TYPE_FLOAT
    };
    typedef std::vector<unsigned char> binary;
    typedef std::string string;
    typedef std::vector<cbor> array;
    typedef std::map<cbor, cbor> map;
    enum simple {
        SIMPLE_FALSE = 20,
        SIMPLE_TRUE,
        SIMPLE_NULL,
        SIMPLE_UNDEFINED,
        null = SIMPLE_NULL,
        undefined = SIMPLE_UNDEFINED
    };

    cbor (unsigned value);
    cbor (uint64_t value);
    cbor (int value);
    cbor (int64_t value);
    cbor (const cbor::binary &value);
    cbor (cbor::binary &&value);
    cbor (const cbor::string &value);
    cbor (cbor::string &&value);
    cbor (const char *value);
    cbor (const cbor::array &value);
    cbor (cbor::array &&value);
    cbor (const cbor::map &value);
    cbor (cbor::map &&value);
    static cbor tagged(uint64_t tag, const cbor &value);
    cbor (cbor::simple value = cbor::SIMPLE_UNDEFINED);
    cbor (bool value);
    cbor (float value);
    cbor (double value);
    cbor (std::nullptr_t);
    cbor(const cbor&);
    cbor(cbor&&);
    ~cbor();

    cbor& operator = (const cbor&);
    cbor& operator = (cbor&&);

    bool is_unsigned () const;
    bool is_signed () const;
    bool is_int () const;
    bool is_binary () const;
    bool is_string () const;
    bool is_array () const;
    bool is_map () const;
    bool is_tagged () const;
    bool is_simple () const;
    bool is_bool () const;
    bool is_null () const;
    bool is_undefined () const;
    bool is_float () const;
    bool is_number () const;
    
    uint64_t to_unsigned () const;
    int64_t to_signed () const;
    cbor::binary const &to_binary() const;
    cbor::string const &to_string() const;
    cbor::array const &to_array() const;
    cbor::map const &to_map() const;
    cbor::simple to_simple () const;
    bool to_bool () const;
    double to_float () const;
    
    operator unsigned () const;
    operator int () const;
    operator cbor::binary const &() const;
    operator cbor::string const &() const;
    operator cbor::array const &() const;
    operator cbor::map const &() const;
    operator cbor::simple () const;
    operator bool () const;
    operator double () const;
    
    uint64_t tag () const;
    cbor const &child() const;
    
    cbor::type_t type () const;
    
    bool read (std::istream &in);
    void write (std::ostream &out) const;
    
    static bool validate (const cbor::binary &in);
    static cbor decode (const cbor::binary &in);
    static cbor::binary encode (const cbor &in);
    static cbor::string debug (const cbor &in);
    
    bool operator == (const cbor &other) const;
    bool operator != (const cbor &other) const;
    
    bool operator <(const cbor &other) const;
    bool operator <=(cbor const &other) const;
    bool operator >(cbor const &other) const;
    bool operator >=(cbor const &other) const;

    void swap(cbor &other);
private:
    cbor::type_t m_type;
    union
    {
        uint64_t m_unsigned;
        int64_t m_integer;
        double m_float;
    };
    union
    {
        cbor::binary *m_binary;
        cbor::string *m_string;
        cbor::array *m_array;
        cbor::map *m_map;
    };

    void destroy();
};

void swap(cbor& left, cbor& right);

// Trivial inline function implementations

inline cbor::operator unsigned() const {
    return to_unsigned();
}

inline cbor::operator int() const {
    return to_signed();
}

inline cbor::operator cbor::binary const &() const {
    return to_binary();
}

inline cbor::operator cbor::string const &() const {
    return to_string();
}

inline cbor::operator cbor::array const &() const {
    return to_array();
}

inline cbor::operator cbor::map const &() const {
    return to_map();
}

inline cbor::operator cbor::simple() const {
    return to_simple();
}

inline cbor::operator bool() const {
    return to_bool();
}

inline cbor::operator double() const {
    return to_float();
}

inline cbor::type_t cbor::type() const {
    return m_type;
}

inline bool cbor::operator !=(cbor const &other) const {
    return !(*this == other);
}

inline bool cbor::operator <=(cbor const &other) const {
    return !(other < *this);
}

inline bool cbor::operator >(cbor const &other) const {
    return other < *this;
}

inline bool cbor::operator >=(cbor const &other) const {
    return !(*this < other);
}

inline cbor::~cbor() {
    destroy();
}

inline void swap(cbor &left, cbor &right) {
    left.swap(right);
}
