#ifndef LUA_RUNTIME_H
#define LUA_RUNTIME_H

#include <string>
#include <set>
#include "lua.h"
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

    ~LuaRuntime();

    void initRuntime(std::string initScriptPath);

protected:
    class LuaVarStorage: public IVariableStorage {
    public:
        LuaVarStorage(lua_State* state);

        virtual void addVariable(const std::string& name,  AbstractVariable* var) override;
        virtual AbstractVariable* getVariable(const std::string& name) const override;
        virtual void updateVariables() override;
        virtual void clear() override;

        void registerVar(const std::string& name);

    protected:
        std::set<std::string> _usedVars;
        lua_State* _state;
    };

protected:
    lua_State* _state;
};

#endif // LUA_RUNTIME_H
