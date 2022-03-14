#ifndef LUA_RUNTIME_H
#define LUA_RUNTIME_H

#include <string>
#include <set>
#include "colproc/runtime/runtime.h"

namespace sol {class state;}

class LuaRuntime: public Runtime {
public:
    LuaRuntime();

    LuaRuntime(
        Canvas* canvas,
        uint32_t frameRate,
        std::string initScriptPath
    );

    virtual ~LuaRuntime();

    void initRuntime(std::string initScriptPath);

protected:
    sol::state* _state;
};

#endif // LUA_RUNTIME_H
