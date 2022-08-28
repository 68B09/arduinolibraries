#include <Stopwatch.h>

Stopwatch::Stopwatch()
{
	this->starttick = 0;
	this->totaltick = 0;
	this->isrun = false;
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::start()
{
	if (!this->isrun) {
		this->starttick = millis();
		this->isrun = true;
	}
}

void Stopwatch::stop()
{
	if (this->isRun()) {
		ulong nowtick = millis();
		this->totaltick += calcElapsed(this->starttick, nowtick);
		this->isrun = false;
	}
}

void Stopwatch::restart()
{
	this->reset();
	this->start();
}

void Stopwatch::reset()
{
	this->totaltick = 0;
	this->isrun = false;
}

ulong Stopwatch::elapsedMillis()
{
	if (this->isRun()) {
		ulong nowtick = millis();
		return calcElapsed(this->starttick, nowtick) + this->totaltick;
	}

	return this->totaltick;
}

ulong Stopwatch::calcElapsed(ulong start, ulong end)
{
	if (end >= start) {
		return end - start;
	}
	return end + (ULONG_MAX - start);
}

bool Stopwatch::isRun()
{
	return this->isrun;
}
