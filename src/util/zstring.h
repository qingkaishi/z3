/*++
Copyright (c) 2011 Microsoft Corporation

Module Name:

    zstring.h

Abstract:

    String wrapper for unicode/ascii internal strings as vectors

Author:

    Nikolaj Bjorner (nbjorner) 2021-01-26

--*/
#pragma once

#include <string>
#include "util/vector.h"
#include "util/buffer.h"

class zstring {
private:
    buffer<unsigned> m_buffer;
    bool well_formed() const;
    bool uses_unicode() const;
    bool is_escape_char(bool from_input, char const *& s, unsigned& result);
public:
    static unsigned unicode_max_char() { return 196607; }
    static unsigned unicode_num_bits() { return 18; }
    static unsigned ascii_max_char() { return 255; }
    static unsigned ascii_num_bits() { return 8; }
    zstring() {}
    zstring(char const* s, bool from_input);
    zstring(const std::string &str) : zstring(str.c_str(), false) {}
    zstring(unsigned sz, unsigned const* s) { m_buffer.append(sz, s); SASSERT(well_formed()); }
    zstring(unsigned ch);
    zstring replace(zstring const& src, zstring const& dst) const;
    zstring reverse() const;
    std::string encode() const;
    unsigned length() const { return m_buffer.size(); }
    unsigned operator[](unsigned i) const { return m_buffer[i]; }
    bool empty() const { return m_buffer.empty(); }
    bool suffixof(zstring const& other) const;
    bool prefixof(zstring const& other) const;
    bool contains(zstring const& other) const;
    int  indexofu(zstring const& other, unsigned offset) const;
    int  last_indexof(zstring const& other) const;
    zstring extract(unsigned lo, unsigned hi) const;
    zstring operator+(zstring const& other) const;
    bool operator==(const zstring& other) const;
    bool operator!=(const zstring& other) const;

    friend std::ostream& operator<<(std::ostream &os, const zstring &str);
    friend bool operator<(const zstring& lhs, const zstring& rhs);
};
