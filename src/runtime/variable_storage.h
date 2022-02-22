#ifndef VARIABLE_STORAGE_H
#define VARIABLE_STORAGE_H

#include "colproc/variable/variable.h"
#include <string>
#include <map>
#include <typeinfo>

class VariableStorage {
public: 
    template <typename T>
    void addVariable(std::string name,  Variable<T>* var) {
        auto it = _storage.find(name);
        if(it != _storage.end()) {
            throw std::runtime_error(
                std::string("Variable: Variable \"") + name + 
                "\" already exists"
            );
        }
    
        _storage.insert(
            std::make_pair(name, (AbstractVariable*)var)
        );
    }
    
    template <typename T>
    Variable<T>* getVariable(std::string name) const {
        auto it = _storage.find(name);
        if(it == _storage.end()) {
            throw std::runtime_error(
                std::string("Variable: Unable to find variable \"")+
                name + "\""
            );
        };

        AbstractVariable* var = it->second;

        if(typeid(T) != var->getVariableType()) {
            throw std::runtime_error(
                std::string("Variable: Can not cast variable from: ") +
                var->getVariableType().name() + " to: " +
                typeid(T).name()
            );
        };

        return var->castToVariable<T>();
    }
    
    void updateVariables() {
        for(auto it: _storage) {
            it.second->updateValue();
        }
    }

    void clear() {
        for(auto it: _storage) {
            delete it.second;
        }
        
        _storage.clear();
    }

protected:
    std::map<std::string, AbstractVariable*> _storage;
};

#endif // VARIABLE_STORAGE_H
