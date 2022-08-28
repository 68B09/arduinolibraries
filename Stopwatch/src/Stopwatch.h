/*
Stopwatch
*/
#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <Arduino.h>

class Stopwatch {
private:
	ulong starttick;
	ulong totaltick;
	bool isrun;

public:
	Stopwatch();
	~Stopwatch();

	void start();
	void stop();
	void restart();
	void reset();
	ulong elapsedMillis();
	bool isRun();
	ulong calcElapsed(ulong start, ulong end);
};

class TimeCalc {
private:
	time_t basetime;

public:
	TimeCalc()
	{
	}

	TimeCalc(const time_t inittime) :TimeCalc()
	{
		this->basetime = inittime;
	}

	time_t getBaseTime() const
	{
		return this->basetime;
	}

	void setBaseTime(const time_t basetime)
	{
		this->basetime = basetime;
	}

	void addSecond(const time_t offset)
	{
		this->basetime += offset;
	}

	time_t getElapsed() const
	{
		return time(NULL) - this->basetime;
	}
};

#endif