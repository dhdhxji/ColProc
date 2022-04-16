#ifndef VALUE_H
#define VALUE_H

#include <typeinfo>
#include <string>
#include <stdexcept>
#include "colproc/util/error.hpp"

template <typename T>
class Variable;

using namespace std::string_literals;

class AbstractVariable {
public:
    virtual ~AbstractVariable() {};

    template <typename T> Variable<T>* castToVariable() {
        ERR_ASSERT_TRUE(
            getVariableType() == typeid(T),
            "Incompatimble variable type. Expected: "s + typeid(T).name() + "; Actual: "s + getVariableType().name()
        );

        return dynamic_cast<Variable<T>*>(this);
    }

    template<class T> inline
    operator Variable<T>* () {
        return castToVariable<T>();
    }

    virtual void updateValue() = 0;
    
    virtual const std::type_info& getVariableType() = 0;
};

template <typename T>
class Variable: public AbstractVariable
{
public:
    virtual ~Variable() {};

    virtual T getValue() {
        return _value;
    }

    operator T() {
        return getValue();
    }

    const std::type_info& getVariableType() override {
        return typeid(T);
    }
protected:
    T _value;
};

#endif // VALUE_H
