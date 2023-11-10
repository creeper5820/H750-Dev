#include "ValueManager.hh"

ValueManager::ValueManager()
{
}

template <typename TypeNew>
void ValueManager::New(char *name, TypeNew value)
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
TypeGet ValueManager::Get(char *name)
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
void ValueManager::Set(char *name, TypeSet value)
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