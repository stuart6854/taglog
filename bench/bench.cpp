#define TAGLOG_HEADER_ONLY
#include <taglog/taglog.hpp>

#include <chrono>

void bench(int iterationCount);

void benchmark_single_threaded(int iterationCount)
{
    taglog::log("**************************************************************");
    taglog::log("Single threaded: {} messages", iterationCount);
    taglog::log("**************************************************************");

    bench(iterationCount);
}

int main()
{
    taglog::init();

    int iterations = 250000;
    benchmark_single_threaded(iterations);

    taglog::terminate();

    return 0;
}

void bench(int iterationCount)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    auto start = high_resolution_clock::now();
    for (auto i = 0; i < iterationCount; ++i)
    {
        taglog::log("Hello Logger: msg number {}", i);
    }

    auto delta = high_resolution_clock ::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();

    taglog::log("{:<30} Elapsed: {:0.2f} secs {:>16L}/sec", "_log_name_", delta_d, int(iterationCount / delta_d));
}
