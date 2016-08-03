// Copyright Doug Moen 2016.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENCE.md or http://www.boost.org/LICENSE_1_0.txt

#include <curv/string.h>
using namespace curv;
using namespace aux;

Shared<String>
curv::String::make(const char* str, size_t len)
{
    void* raw = malloc(sizeof(String) + len);
    if (raw == nullptr)
        throw std::bad_alloc();
    String* s = new(raw) String();
    memcpy(s->data_, str, len);
    s->data_[len] = '\0';
    s->size_ = len;
    return Shared<String>(s);
}

Shared<String>
String_Builder::get_string()
{
    return String::make(str().data(), str().size());
}

void
curv::String::print(std::ostream& out) const
{
    out << '"';
    for (size_t i = 0; i < size_; ++i) {
        char c = data_[i];
        if (c == '$' || c == '"')
            out << '$';
        out << c;
    }
    out << '"';
}
