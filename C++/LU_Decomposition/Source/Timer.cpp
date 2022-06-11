#include "../Header/Timer.h"

Timer::time_type Timer::start_timer() {
	return std::chrono::steady_clock::now();
}

void Timer::end_timer(Timer::time_type start) {
	//Stop count the time.
	auto end = std::chrono::steady_clock::now();

	// Store the time difference between start and end
	auto diff = end - start;
	std::cout << "\nTotal Time Taken = \n";
	std::cout << std::chrono::duration <double, std::milli > (diff).count() << " ms" << " = ";

	std::cout << std::chrono::duration <double>(diff).count() << " sec" << std::endl;
}