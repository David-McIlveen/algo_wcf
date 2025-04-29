#include "stopwatch.hpp"

void StopWatch::start(){
    if(_is_running) throw "Cannot start stop watch when it's already started!";
    _start_time = std::chrono::high_resolution_clock::now();
    _is_running = true;
}

void StopWatch::stop(){
    if(!_is_running) throw "You'll need to start the stop watch before you can stop it!";
    _end_time = std::chrono::high_resolution_clock::now();
    _has_data = true;
    _is_running = false;
    _time = std::chrono::duration_cast<std::chrono::nanoseconds>(_end_time - _start_time).count();
}

long long StopWatch::get_ns_time(){
    if(!_has_data) throw "Error with data, as there's none present.";
    return _time;
}