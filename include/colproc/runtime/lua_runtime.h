#ifndef LUA_RUNTIME_H
#define LUA_RUNTIME_H

#include <string>
#include "lua.h"
#include "colproc/runtime/runtime.h"

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
    lua_State* _state;
};

#endif // LUA_RUNTIME_H
