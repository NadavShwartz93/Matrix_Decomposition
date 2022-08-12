#ifndef TIMER_
#define TIMER_
#include <chrono>		//for timer
#include <iostream>

using time_type = std::chrono::time_point<std::chrono::steady_clock>;

//Methods for timer:
namespace my_timer {
	time_type start_timer();
	void end_timer(time_type start);
};

////Methods for time:
namespace my_timer {
	time_type start_timer() {

        return std::chrono::steady_clock::now();
	}

	void end_timer(time_type start) {
		//Stop count the time.
        auto end = std::chrono::steady_clock::now();

		// Store the time difference between start and end
		auto diff = end - start;

        std::cout << "\nTotal Time Taken = \n";
        std::cout << std::chrono::duration <double, std::milli>(diff).count() << " ms" << std::endl;
	}
};
#endif // !TIMER_

