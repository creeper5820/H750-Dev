#pragma once

#include "string"
#include "main.h"
#include "map"
#include "typeinfo"

class Value
{
public:
    std::string name;
    std::type_info type;
    union {
        float value_float;
        int value_int;
    };

    Value(){};
};

class ValueManager
{
private:
    std::map<std::string, Value> value_map_;

public:
    ValueManager(){};

    template <typename TypeNew>
    void New(const char *name, TypeNew value)
    {
        Value temp_value;

        temp_value.name = name;
        temp_value.type = typeid(value);

        switch (typeid(value)) {
            case typeid(float):
                temp_value.value_float = value;
            case typeid(int):
                temp_value.value_int = value;
            default:
                break;
        }

        value_map_.insert(std::pair<std::string, Value>(name, temp_value));
    }

    template <typename TypeGet>
    TypeGet Get(char *name)
    {
        auto iter = value_map_.find(name);
        if (iter == value_map_.end())
            return (int)0;

        Value temp_value = iter->second;

        switch (temp_value.type) {
            case typeid(float):
                return temp_value.value_float;
            case typeid(int):
                return temp_value.value_int;
            default:
                break;
        }
    }

    template <typename TypeSet>
    void Set(char *name, TypeSet value)
    {
        auto iter = value_map_.find(name);
        if (iter == value_map_.end())
            return;

        Value temp_value = iter->second;

        switch (typeid(value)) {
            case typeid(float):
                temp_value.value_float = value;
            case typeid(int):
                temp_value.value_int = value;
            default:
                break;
        }
    }
};