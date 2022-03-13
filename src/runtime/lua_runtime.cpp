#include "colproc/runtime/lua_runtime.h"

#include "sol/sol.hpp"
#include "colproc/lua/bindings.h"

LuaRuntime::LuaRuntime(): 
    Runtime()
{
    colproc_build_lua_state(_state);
}

LuaRuntime::LuaRuntime(
    Canvas* canvas,
    uint32_t frameRate,
    std::string initScriptPath
): 
    Runtime(canvas, nullptr, frameRate)
{
    colproc_build_lua_state(_state);
    initRuntime(initScriptPath);
}


void LuaRuntime::initRuntime(std::string initScriptPath) {
    _state.script_file(initScriptPath);

    ColProc* rt = _state["RenderTree"];

    setRenderNode(rt);
}

LuaRuntime::LuaVarStorage::LuaVarStorage(sol::state& s): _state(s) {}

void LuaRuntime::LuaVarStorage::addVariable(
    const std::string& name,  AbstractVariable* var
) {
    _state[name] = var;
    registerVar(name);
}

AbstractVariable* LuaRuntime::LuaVarStorage::getVariable(const std::string& name) const {
    AbstractVariable* val = _state[name];

    return val;
}

void LuaRuntime::LuaVarStorage::updateVariables() {
    for(string name: _usedVars) {
        getVariable(name)->updateValue();
    }
}

void LuaRuntime::LuaVarStorage::clear() {
    _usedVars.clear();
}

void LuaRuntime::LuaVarStorage::registerVar(const std::string& name) {
    _usedVars.insert(name);
}