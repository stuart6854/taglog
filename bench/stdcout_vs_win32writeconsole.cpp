#define TAGLOG_HEADER_ONLY
#include "taglog/taglog.hpp"

#include <chrono>

#ifndef _WIN32
    #error Can only be compiled on Windows platform!
#endif

#define NOMINMAX
#include <windows.h>

void bench_std_cout(int iterationCount);
void bench_win32_writeconsole(int iterationCount);

void benchmark_single_threaded(int iterationCount)
{
    taglog::log("**************************************************************");
    taglog::log("Single threaded: {} messages", iterationCount);
    taglog::log("**************************************************************");

    //    bench_std_cout(iterationCount);
    bench_win32_writeconsole(iterationCount);
}

int main()
{
    taglog::init();

    int iterations = 250000;
    benchmark_single_threaded(iterations);

    taglog::terminate();

    return 0;
}

// elapsed 6.02 secs
void bench_std_cout(int iterationCount)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    auto start = high_resolution_clock::now();
    for (auto i = 0; i < iterationCount; ++i)
    {
        const auto x = std::format("Hello Logger: msg number {}\n", i);
        std::cout << x;
    }

    auto delta = high_resolution_clock ::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();

    taglog::log("{:<30} Elapsed: {:0.2f} secs {:>16L}/sec", "std::cout", delta_d, int(iterationCount / delta_d));
}

// elapsed: 6.03 secs
void bench_win32_writeconsole(int iterationCount)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    auto start = high_resolution_clock::now();
    for (auto i = 0; i < iterationCount; ++i)
    {
        const auto x = std::format("Hello Logger: msg number {}\n", i);
        WriteConsoleA(stdOut, x.c_str(), x.length(), nullptr, nullptr);
    }

    auto delta = high_resolution_clock ::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();

    taglog::log("{:<30} Elapsed: {:0.2f} secs {:>16L}/sec", "Win32 WriteConsole", delta_d, int(iterationCount / delta_d));
}
