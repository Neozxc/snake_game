#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <thread>

class Timer
{
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    explicit Timer(double ticksPerSecond)
        : tickDuration(std::chrono::milliseconds(static_cast<int>(1000.0 / ticksPerSecond))),
          lastTick(Clock::now()) {}

    void waitNextTick()
    {
        TimePoint now = Clock::now();
        TimePoint nextTick = lastTick + tickDuration;

        if (now < nextTick)
        {
            std::this_thread::sleep_until(nextTick);
        }

        lastTick = Clock::now();
    }

private:
    std::chrono::milliseconds tickDuration;
    TimePoint lastTick;
};

#endif