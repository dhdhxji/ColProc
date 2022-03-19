#ifndef IVARIABLE_STORAGE_H
#define IVARIABLE_STORAGE_H

#include <string>
#include "colproc/variable/variable.h"


using std::string;


class IVariableStorage {
public:
    virtual void addVariable(const string& name,  AbstractVariable* var) = 0;
    virtual AbstractVariable* getVariable(const string& name) const = 0;
    virtual void updateVariables() = 0;
    virtual void clear() = 0;

    virtual string addAnonymousVariable(AbstractVariable* var) {
        string name = "_anonymous_" + anonymousVarCount;
        anonymousVarCount++;

        addVariable(name, var); 

        return name;
    }

protected:
    uint32_t anonymousVarCount = 0;
};

#endif // IVARIABLE_STORAGE_H
