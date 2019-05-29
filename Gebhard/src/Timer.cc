#include "timer.h"

Timer::Timer()
{
	running=0;
}

void Timer::start()
{
	gettimeofday(&StartTime, &Dummy);
    running=1;
}

void Timer::stop()
{
	gettimeofday(&StopTime, &Dummy);
   	running=0;
   	millidiff=(StopTime.tv_usec-StartTime.tv_usec)/1000;
    seconds=StopTime.tv_sec-StartTime.tv_sec-((millidiff<0)?1:0);
    milliseconds=(millidiff>=0) ? millidiff:1000+millidiff;
}

