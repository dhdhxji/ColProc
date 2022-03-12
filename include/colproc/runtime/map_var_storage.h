#ifndef VARIABLE_STORAGE_H
#define VARIABLE_STORAGE_H

#include "colproc/variable/variable.h"
#include "colproc/runtime/ivariable_storage.h"
#include <string>
#include <map>

class MapVarStorage: public IVariableStorage {
public: 
    virtual void addVariable(const string& name,  AbstractVariable* var) override;
    virtual AbstractVariable* getVariable(const string& name) const override;
    virtual void updateVariables() override;
    virtual void clear() override;

protected:
    std::map<string, AbstractVariable*> _storage;
};

#endif // VARIABLE_STORAGE_H
