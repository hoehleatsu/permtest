/*------------------------------------------------------------------------*/
/*                                                                        */
/*  TIMER.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __TIMER_H )
#define __TIMER_H

#include <sys/time.h>
 //extern "C" {int gettimeofday(timeval*,timezone*);}

class Timer
{
public:
    Timer();
    void start();
    void stop();

    unsigned long time() const {return (running ? 0 : seconds);};
    unsigned long millitime() const {return (running ? 0 : milliseconds);};
private:
	struct timezone Dummy;
	timeval StartTime, StopTime;
	int millidiff;
    int running;
    unsigned long seconds;
    unsigned long milliseconds;
};

#endif  // __TIMER_H
