#ifndef BIMAP_H
#define BIMAP_H

#include <iostream>
#include <map>
#include <string>
#include "../Config.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

template<typename KeyType, typename ValueType>
class BiMap {
public:
    // 插入键值对
    void insert(const KeyType& key, const ValueType& value) {
        keyToValue[key] = value;
        valueToKey[value] = key;
    }

    // 根据键查找值
    ValueType getValue(const KeyType& key) const {
        auto it = keyToValue.find(key);
        if (it != keyToValue.end()) {
            return it->second;
        }
        throw std::runtime_error("Key not found");
    }

    // 根据值查找键
    KeyType getKey(const ValueType& value) const {
        auto it = valueToKey.find(value);
        if (it != valueToKey.end()) {
            return it->second;
        }
        throw std::runtime_error("Value not found");
    }

    // 删除键值对
    void eraseByKey(const KeyType& key) {
        auto it = keyToValue.find(key);
        if (it != keyToValue.end()) {
            valueToKey.erase(it->second);
            keyToValue.erase(it);
        }
    }

    void eraseByValue(const ValueType& value) {
        auto it = valueToKey.find(value);
        if (it != valueToKey.end()) {
            keyToValue.erase(it->second);
            valueToKey.erase(it);
        }
    }

    // 检查是否包含键或值
    bool containsKey(const KeyType& key) const {
        return keyToValue.find(key) != keyToValue.end();
    }

    bool containsValue(const ValueType& value) const {
        return valueToKey.find(value) != valueToKey.end();
    }

private:
    std::map<KeyType, ValueType> keyToValue;
    std::map<ValueType, KeyType> valueToKey;
};

// int main() {
//     BiMap<int, std::string> biMap;
//     biMap.insert(1, "One");
//     biMap.insert(2, "Two");

//     // 根据键查找值
//     std::cout << "Key 1 maps to value: " << biMap.getValue(1) << std::endl;

//     // 根据值查找键
//     std::cout << "Value 'Two' maps to key: " << biMap.getKey("Two") << std::endl;

//     // 删除键值对
//     biMap.eraseByKey(1);

//     // 检查是否包含某个键或值
//     if (biMap.containsKey(1)) {
//         std::cout << "Key 1 is in the map." << std::endl;
//     } else {
//         std::cout << "Key 1 is not in the map." << std::endl;
//     }

//     return 0;
// }

GIMC_NAMESPACE_END

#endif // BIMAP_H