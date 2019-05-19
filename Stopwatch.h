#ifndef STOPWATCH_HAS_BEEN_INCLUDED
#define STOPWATCH_HAS_BEEN_INCLUDED

#include <chrono>

class Stopwatch
{
public:
    using Clock        = std::chrono::high_resolution_clock;
    using Seconds      = std::chrono::seconds;
    using Milliseconds = std::chrono::milliseconds;
    using Microseconds = std::chrono::microseconds;
    using Nanoseconds  = std::chrono::nanoseconds;

    void start() {
        mRunning = true;
        mStart = Clock::now();
    }

    void stop() {
        mStop = Clock::now();
        mRunning = false;
    }

    template <typename T>
    double elapsed() {
        if (!mRunning) {
            return std::chrono::duration_cast<T>(mStop - mStart).count();
        } else {
            return std::chrono::duration_cast<T>(Clock::now() - mStart).count();
        }
    }

    double elapsedSeconds() { return elapsed<Seconds>(); }
    double elapsedMilliseconds() { return elapsed<Milliseconds>(); }
    double elapsedMicroseconds() { return elapsed<Microseconds>(); }
    double elapsedNanoseconds() { return elapsed<Nanoseconds>(); }

private:
    bool mRunning;
    Clock::time_point mStart;
    Clock::time_point mStop;
};

#endif // STOPWATCH_HAS_BEEN_INCLUDED





