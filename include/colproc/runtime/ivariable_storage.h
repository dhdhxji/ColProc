#ifndef IVARIABLE_STORAGE_H
#define IVARIABLE_STORAGE_H

#include <string>
#include "colproc/variable/variable.h"


using std::string;


class IVariableStorage {
public:
    virtual void addVariable(string name,  AbstractVariable* var) = 0;
    virtual AbstractVariable* getVariable(string name) const = 0;
    virtual void updateVariables() = 0;
    virtual void clear() = 0;
};

#endif // IVARIABLE_STORAGE_H
