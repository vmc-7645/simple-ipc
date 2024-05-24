#ifndef DATA_H
#define DATA_H

#include <string>

struct Data {
    int intValue;
    float floatValue;
    std::string stringValue;
    enum Type { type1, type2, type3 } typeValue;
};

#endif // DATA_H