#include <chrono>
#include "funclib.hpp"

class Timer {
public:
    Timer() : is_running(false), elapsed_time(0) {}

    void Start() {
        if (!is_running) {
            start_time_point = std::chrono::high_resolution_clock::now();
            is_running = true;
        }
    }

    void Stop() {
        if (is_running) {
            auto end_time_point = std::chrono::high_resolution_clock::now();
            elapsed_time += std::chrono::duration<double>(end_time_point - start_time_point).count();
            is_running = false;
        }
    }

    void Restart() {
        elapsed_time = 0;
        start_time_point = std::chrono::high_resolution_clock::now();
        is_running = true;
    }

    double ElapsedMilliseconds() const {
        if (is_running) {
            auto current_time_point = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double, std::milli>(current_time_point - start_time_point).count() + elapsed_time * 1000;
        }
        else {
            return elapsed_time * 1000;
        }
    }

    double ElapsedSeconds() const {
        if (is_running) {
            auto current_time_point = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double>(current_time_point - start_time_point).count() + elapsed_time;
        }
        else {
            return elapsed_time;
        }
    }

    void Reset() {
        is_running = false;
        elapsed_time = 0;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
    bool is_running;
    double elapsed_time;
};


static double func1(const double x, const double y) {
    return (y + x);
}

static double func2(const double x, const double y) {
    return 2 * (y + x);
}
static double func3(const double x, const double y) {
    return (2 * y + 2 * x);
}
static double func4(const double x, const double y) {
    return ((1.23 * x * x) / y) - 123.123;
}
static double func5(const double x, const double y) {
    return (y + x / y) * (x - y / x);
}
static double func6(const double x, const double y) {
    return x / ((x + y) + (x - y)) / y;
}
static double func7(const double x, const double y) {
    return 1 - ((x * y) + (y / x)) - 3;
}
static double func8(const double x, const double y) {
    return (5.5 + x) + (2.0 * x - 2.0 / 3.0 * y) * (x / 3.0 + y / 4.0) + (y + 7.7);
}
static double func9(const double x, const double y) {
    return sin(2 * x) + cos(FNL_PI / y);
}
static double func10(const double x, const double y) {
    return 1 - sin(2 * x) + cos(FNL_PI / y);
}
static double func11(const double x, const double y) {
    return sqrt(111.111 - sin(2 * x) + cos(FNL_PI / y) / 333.333);
}
static double func12(const double x, const double y) {
    return x + (cos(y - sin(2 / x * FNL_PI)) - sin(x - cos(2 * y / FNL_PI))) - y;
}
static double func13(const double x, const double y) {
    return std::max(3.33, std::min(sqrt(1 - sin(2 * x) + cos(FNL_PI / y) / 3), 1.11));
}

const std::string global_expression_list[]
= {
     "(y + x)",
     "2 * (y + x)",
     "(2 * y + 2 * x)",
     "((1.23 * x*x) / y) - 123.123",
     "(y + x / y) * (x - y / x)",
     "x / ((x + y) + (x - y)) / y",
     "1 - ((x * y) + (y / x)) - 3",
     "(5.5 + x) + (2 * x - 2 / 3 * y) * (x / 3 + y / 4) + (y + 7.7)",
     "sin(2 * x) + cos(pi / y)",
     "1 - sin(2 * x) + cos(pi / y)",
     "sqrt(111.111 - sin(2 * x) + cos(pi / y) / 333.333)",
     "x + (cos(y - sin(2 / x * pi)) - sin(x - cos(2 * y / pi))) - y",
     "max(3.33, min(sqrt(1 - sin(2 * x) + cos(pi / y) / 3), 1.11))"
};

typedef double (*nativefunc)(const double, const double);

const nativefunc natives[] = {
    func1, func2, func3, func4,func5, func6,func7, func8,func9, func10, func11, func12, func13
};

const double call_native(size_t i, const double a, const double b) {
    return natives[i](a, b);
    /*switch (i)
    {
    case 0:
        return func1(a, b);
    default:
        break;
    }*/
}

void CompareNative(int iter) {

    Timer timer;

    double vmtimes[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
    double nativetimes[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

    for (size_t i = 0; i < 13; i++)
    {
        funclib::FuncVM vm;
        funclib::Function fx = vm.CreateFunction("f(x,y)", global_expression_list[i]);
    
        double resultvm = 0, resultnat = 0;
        double a = (rand() % INT32_MAX) * 2.0 + 0.5;
        double b = (rand() % INT32_MAX) * 2.0 + 0.5;
        fx.SetArgs(a, b);

        timer.Start();
        for (size_t k = 0; k < iter; k++)
        {
            double result = fx.Call();
        }
        timer.Stop();
        vmtimes[i] = timer.ElapsedMilliseconds();

        timer.Restart();
        for (size_t k = 0; k < iter; k++)
        {
            double result = natives[i](a, b);
        }
        timer.Stop();
        nativetimes[i] = timer.ElapsedMilliseconds();
        timer.Reset();
    }

    for (size_t i = 0; i < 13; i++)
    {
        double percent = 100.0 * nativetimes[i] / vmtimes[i];
        std::cout << "Func " << i << " VM: " << vmtimes[i] << " ms  Native: " << nativetimes[i] << " ms\n\n";
    }
}