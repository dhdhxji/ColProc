#include <iostream>
#include <exception>
#include <string>
#include "../util/console_canvas.h"
#include "colproc/runtime/lua_runtime.h"
#include "colproc/variable/variable_callback.h"
#include "colproc/util/error.hpp"


#define REFRESH_RATE_HZ 30
#define MATRIX_W        19
#define MATRIX_H        7


using namespace std::string_literals;





int main() {
    CanvasConsole canvas(MATRIX_W, MATRIX_H);
    
    try {
        LuaRuntime rt(&canvas, 30);

        rt.getVariableManager().addVariable(
            "hrs",
            new VariableCallback<std::string>([](){
                time_t ttime = time(0);
                struct tm* tm_time = localtime(&ttime);
                return  std::to_string(tm_time->tm_hour);
            })
        );

        rt.getVariableManager().addVariable(
            "mins",
            new VariableCallback<std::string>([](){
                time_t ttime = time(0);
                struct tm* tm_time = localtime(&ttime);
                return  std::to_string(tm_time->tm_min);
            })
        );

        rt.loadScript("../init.lua");

        rt.runRenderLoop();
    } catch(std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unexpected error" << std::endl;
    }
    
    return 0;
}