#include "../util/console_canvas.h"
#include "colproc/gen/text.h"
#include "colproc/variable/variable_constant.h"
#include <memory>
#include <string>

#include <chrono>


#define REFRESH_RATE_HZ 30
#define MATRIX_W        19
#define MATRIX_H        7


using namespace std::chrono;
using std::string;


int main(int argc, char** argv)
{
    CanvasConsole canvas(MATRIX_W, MATRIX_H);

    auto text = std::make_unique<VariableConstant<string>>("Hello");
    auto font = std::make_unique<VariableConstant<string>>("3_by_57");
    GeneratorText gen(text.get(), font.get());

    for(;;) {
        uint32_t time = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
        ).count();

        gen.generate(0, 0, time, &canvas);

        canvas.display();
        canvas.clear();
    }
}
