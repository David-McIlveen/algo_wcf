#include "testing.hpp"

TimeTest::TimeTest(fs::path output_csv){
    _output_csv = output_csv;
    _output_stream = ofstream(output_csv);
    _timer = new StopWatch();
    _running_total = 0;
    _trial_number = 0;
}

TimeTest::~TimeTest(){
    delete _timer;
    _output_stream.close();
}

void TimeTest::start_test(string title){
    if(_trial_number = 0){
        _output_stream << title << ",";
    }
}

void TimeTest::start(){
    _timer->start();
}

void TimeTest::stop(){
    _timer->stop();
    long long time = _timer->get_ns_time();
    _running_total += time;
    _output_stream << time << ",";
    _trial_number += 1;
}

void TimeTest::next_test(){
    double avg = (1.0 * _running_total) / _trial_number;
    _output_stream << avg << endl;
    _running_total = 0;
    _trial_number = 0;
}

string TimeTest::get_file_name(){
    return _output_csv.string();
}