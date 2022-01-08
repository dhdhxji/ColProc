#ifndef VALUE_CALLBACK_H
#define VALUE_CALLBACK_H

#include "colproc/variable/variable.h"
#include <functional>

template <class T>
class VariableCallback: public Variable<T> 
{
public:
    VariableCallback(std::function<T()> cb) {
        _callback = cb;
    }

    virtual void updateValue() override {
        Variable<T>::_value = _callback();
        //pritnf("updated value %s\n", )
    }

protected:
    std::function<T()> _callback;
};

#endif // VALUE_CALLBACK_H
