#ifndef CPP_STOP_WATCH
#define CPP_STOP_WATCH

#include <chrono>

class StopWatch{
    public:
        // Starts the stopwatch (Errors if called when started)
        void start();
        // Stops the stopwatch (Errors if called when not started)
        void stop();
        // 0 until start and stop are called. (Errors when no data is available)
        long long get_ns_time();
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _start_time;
        std::chrono::time_point<std::chrono::high_resolution_clock> _end_time;
        bool _is_running = false;
        bool _has_data = false;
        long long _time = 0;
};

#endif
