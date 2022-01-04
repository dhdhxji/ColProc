#ifndef VALUE_H
#define VALUE_H

#include <typeinfo>
#include <string>
#include <stdexcept>

template <typename T>
class Variable;

class AbstractVariable {
public:
    template <typename T> Variable<T>* castToVariable() {
        if(getVariableType() != typeid(T)) {
            throw std::runtime_error(
                std::string("Incompatimble variable type. Expected: ") + 
                typeid(T).name() + "; Actual: " + getVariableType().name()
            );
        }

        return dynamic_cast<Variable<T>*>(this);
    }
    
    virtual const std::type_info& getVariableType() = 0;
};

template <typename T>
class Variable: public AbstractVariable
{
public:
    virtual T getValue() {
        return _value;
    }

    operator T() {
        return getValue();
    }

    virtual void updateValue() = 0;

    const std::type_info& getVariableType() override {
        return typeid(T);
    }
protected:
    T _value;
};

#endif // VALUE_H
