#ifndef _TIMER_
#define _TIMER_

#include<chrono>		//for timer
#include<iostream>

class Timer
{
public:
	using time_type = typename std::chrono::time_point<std::chrono::steady_clock>;

	static time_type start_timer();

	static void end_timer(time_type start);

private:

};

#endif // !_TIMER_