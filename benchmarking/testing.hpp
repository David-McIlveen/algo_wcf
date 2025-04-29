#ifndef CPP_TIME_TESTING
#define CPP_TIME_TESTING

#include <string>
#include <filesystem>
#include <fstream>

#include "stopwatch.hpp"

using namespace std;
namespace fs = std::filesystem;

// Used to test different algorithms of different sizes.
// NOTE - This class is very dependent on external outputs / calls for a good formatting. It's up to you to call start_test, as well as call start and stop the same number of times between tests. The average will always be the last number.
class TimeTest{
    public:
        // Sets file and opens fstream
        TimeTest(fs::path output_csv);
        // Not required, but gives a title to the row of tests. (Must be called before any starts are called)
        void start_test(string title);
        // Starts timeing test
        void start();
        // Stops timeing test and prints number to file
        void stop();
        // Averages all tests and moves onto the next one
        void next_test();
        // Returns the name of the test.
        string get_file_name();
        // Closes fstream
        ~TimeTest();
    private:
        fs::path _output_csv;
        ofstream _output_stream;
        StopWatch* _timer;
        long long _running_total;
        int _trial_number;
};

#endif