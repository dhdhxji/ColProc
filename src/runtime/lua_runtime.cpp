#include "colproc/runtime/lua_runtime.h"
#include "colproc/lua/bindings.h"

#include "lauxlib.h"
#include "lualib.h"
#include "LuaBridge/LuaBridge.h"


LuaRuntime::LuaRuntime(): 
    Runtime(),
    _state(colproc_build_lua_state())
{}

LuaRuntime::LuaRuntime(
    Canvas* canvas,
    uint32_t frameRate,
    std::string initScriptPath
): 
    Runtime(canvas, nullptr, frameRate),
    _state(colproc_build_lua_state())
{
    initRuntime(initScriptPath);
}

LuaRuntime::~LuaRuntime() {
    lua_gc(_state, LUA_GCCOLLECT, 0);
    lua_close(_state);
}

//TODO: Implement cusom variable manager
void LuaRuntime::initRuntime(std::string initScriptPath) {
    int status = luaL_dofile(_state, initScriptPath.c_str());
    if(status != 0) {
        std::string errMsg = lua_tostring(_state, -1);
        lua_pop(_state, 1);

        throw std::runtime_error("[LUA]: Init script error: " + errMsg);
    }
    
    auto rt = luabridge::getGlobal(_state, "RenderTree").cast<ColProc*>();
    if(rt == nullptr) {
        throw std::runtime_error("[LUA]: Root render node is not set");
    }
    setRenderNode(rt);
}