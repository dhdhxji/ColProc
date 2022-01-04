#ifndef VALUE_CONSTANT_H
#define VALUE_CONSTANT_H

#include "colproc/variable/variable.h"

template <class T>
class VariableConstant: public Variable<T> {
public:
    VariableConstant(const T& value) {
        Variable<T>::_value = value;
    }

    virtual void updateValue() override {
        //Do nothing, value is constant
    }
};

#endif // VALUE_CONSTANT_H
