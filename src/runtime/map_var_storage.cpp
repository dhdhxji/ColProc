#include "colproc/runtime/map_var_storage.h"

#include "colproc/util/error.hpp"

MapVarStorage::~MapVarStorage() {
    clear();
}

void MapVarStorage::addVariable(const string& name, AbstractVariable* var) {
    auto it = _storage.find(name);
    ERR_ASSERT_TRUE(it == _storage.end(), "Variable: Variable \"" + name + "\" already exists");

    _storage.insert(
        std::make_pair(name, (AbstractVariable*)var)
    );
}

AbstractVariable* MapVarStorage::getVariable(const string& name) const {
    auto it = _storage.find(name);
    ERR_ASSERT_FALSE(it == _storage.end(), "Variable: Unable to find variable \"" + name + "\"");

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