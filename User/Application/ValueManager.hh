#pragma once

#include "string"
#include "main.h"
#include "map"
#include "typeinfo"

typedef struct Value {
    std::string name;
    std::type_info type;
    union {
        float value_float;
        int value_int;
    };
} Value;

class ValueManager
{
private:
    std::map<std::string, Value> value_map_;

public:
    ValueManager();

    template <typename TypeNew>
    void New(char *name, TypeNew value);

    template <typename TypeGet>
    TypeGet Get(char *name);

    template <typename TypeSet>
    void Set(char *name, TypeSet value);
};