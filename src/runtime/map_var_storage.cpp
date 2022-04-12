#include "colproc/runtime/map_var_storage.h"

MapVarStorage::~MapVarStorage() {
    clear();
}

void MapVarStorage::addVariable(const string& name, AbstractVariable* var) {
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

AbstractVariable* MapVarStorage::getVariable(const string& name) const {
    auto it = _storage.find(name);
    if(it == _storage.end()) {
        throw std::runtime_error(
            std::string("Variable: Unable to find variable \"")+
            name + "\""
        );
    };

    return it->second;
}

void MapVarStorage::updateVariables() {
    for(auto it: _storage) {
        it.second->updateValue();
    }
}

void MapVarStorage::clear() {
    for(auto it: _storage) {
        delete it.second;
    }
    
    _storage.clear();
}