#include "../util/console_canvas.h"
#include "colproc/gen/rainbow.h"
#include "colproc/variable/variable_constant.h"
#include <memory>

#include <chrono>


#define REFRESH_RATE_HZ 30
#define MATRIX_W        19
#define MATRIX_H        7


using namespace std::chrono;


int main(int argc, char** argv)
{
    CanvasConsole canvas(MATRIX_W, MATRIX_H);

    auto length = std::make_unique<VariableConstant<int32_t>>(10);
    auto angle = std::make_unique<VariableConstant<int32_t>>(10);
    auto period = std::make_unique<VariableConstant<int32_t>>(10000);
    GeneratorRainbow gen(length.get(), angle.get(), period.get());

    for(;;) {
        uint32_t time = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
        ).count();

        gen.generate(0, 0, time, &canvas);

        canvas.display();
        canvas.clear();
    }
}
