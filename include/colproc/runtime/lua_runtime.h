#ifndef LUA_RUNTIME_H
#define LUA_RUNTIME_H

#include <string>
#include <set>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "sol/sol.hpp"
#include "colproc/runtime/runtime.h"
#include "colproc/runtime/ivariable_storage.h"

class LuaRuntime: public Runtime {
public:
    LuaRuntime();

    LuaRuntime(
        Canvas* canvas,
        uint32_t frameRate,
        std::string initScriptPath
    );

    ~LuaRuntime() = default;

    void initRuntime(std::string initScriptPath);

protected:
    class LuaVarStorage: public IVariableStorage {
    public:
        LuaVarStorage(sol::state& s);

        virtual void addVariable(const std::string& name,  AbstractVariable* var) override;
        virtual AbstractVariable* getVariable(const std::string& name) const override;
        virtual void updateVariables() override;
        virtual void clear() override;

        void registerVar(const std::string& name);

    protected:
        std::set<std::string> _usedVars;
        sol::state& _state;
    };

protected:
    sol::state _state;
};

#endif // LUA_RUNTIME_H
