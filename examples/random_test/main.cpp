#include "../util/console_canvas.h"
#include "colproc/gen/random.h"

#include <chrono>


#define REFRESH_RATE_HZ 30
#define MATRIX_W        19
#define MATRIX_H        7


using namespace std::chrono;


int main(int argc, char** argv)
{
    CanvasConsole canvas(MATRIX_W, MATRIX_H);

    GeneratorRandom gen(1000);

    for(;;) {
        uint32_t time = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
        ).count();

        gen.generate(0, 0, time, &canvas);

        canvas.display();
        canvas.clear();
    }
}
