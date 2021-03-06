#include "colproc/runtime/lua_runtime.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "sol/sol.hpp"

#include "colproc/lua/bindings.h"
#include "colproc/runtime/ivariable_storage.h"
#include "colproc/util/error.hpp"



class LuaVarStorage: public IVariableStorage {
public:
    LuaVarStorage(sol::state& s): _state(s) {};

    virtual void addVariable(const std::string& name,  AbstractVariable* var) override {
        _state[name] = var;
        registerVar(name);
    }

    virtual AbstractVariable* getVariable(const std::string& name) const override {
        AbstractVariable* val = _state[name];

        return val;
    }

    virtual void updateVariables() override {
        for(string name: _usedVars) {
            getVariable(name)->updateValue();
        }
    }

    virtual void clear() override  {
        _usedVars.clear();
    }

    void registerVar(const std::string& name) {
        _usedVars.insert(name);
    }

protected:
    std::set<std::string> _usedVars;
    sol::state& _state;
};



LuaRuntime::LuaRuntime(): 
    Runtime()
{
    _state = new sol::state;
    _varManager.reset(new LuaVarStorage(*_state));
    colproc_build_lua_state(*_state, getVariableManager());
}

LuaRuntime::LuaRuntime(
    Canvas* canvas,
    uint32_t frameRate
): 
    Runtime(canvas, nullptr, frameRate)
{
    _state = new sol::state;
    _varManager.reset(new LuaVarStorage(*_state));
    colproc_build_lua_state(*_state, getVariableManager());
}

LuaRuntime::LuaRuntime(
    Canvas* canvas,
    uint32_t frameRate,
    std::string initScriptPath
): 
    Runtime(canvas, nullptr, frameRate)
{
    _state = new sol::state;
    _varManager.reset(new LuaVarStorage(*_state));
    colproc_build_lua_state(*_state, getVariableManager());
    loadScript(initScriptPath);
}

LuaRuntime::~LuaRuntime() {
    delete _state;
}


void LuaRuntime::loadScript(std::string initScriptPath) {
    _state->script_file(initScriptPath);

    setRenderNode(getVar_s<ColProc>("RenderTree"));
}

template<class T> inline
T* LuaRuntime::getVar_s(const std::string& name) {
    ERR_ASSERT_FALSE((*_state)[name] == sol::nil, "Variable " + name + " is not set");
  
    T* res = (*_state)[name];

    ERR_CHECK_NOT_NULL(res, "Variable " + name + " has invalid type.");

    return res;
}