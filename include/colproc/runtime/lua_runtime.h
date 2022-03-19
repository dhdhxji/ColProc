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
        uint32_t frameRate
    );

    LuaRuntime(
        Canvas* canvas,
        uint32_t frameRate,
        std::string initScriptPath
    );

    virtual ~LuaRuntime();

    void loadScript(std::string initScriptPath);

protected:
    template<class T> inline
    T* getVar_s(const std::string& name);

protected:
    sol::state* _state;
};

#endif // LUA_RUNTIME_H
