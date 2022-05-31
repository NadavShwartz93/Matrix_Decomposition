#ifndef TIMER_
#define TIMER_
#include<chrono>		//for timer

using time_type = std::chrono::time_point<std::chrono::steady_clock>;

//Methods for timer:
namespace my_timer {
	time_type start_timer();
	void end_timer(time_type start);
};

////Methods for time:
namespace my_timer {
	time_type start_timer() {
		return chrono::steady_clock::now();
	}

	void end_timer(time_type start) {
		//Stop count the time.
		auto end = chrono::steady_clock::now();

		// Store the time difference between start and end
		auto diff = end - start;
		cout << "\nTotal Time Taken = \n";
		cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	}
};
#endif // !TIMER_

