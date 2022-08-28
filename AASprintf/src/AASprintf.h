/*
Auto Allocate sprintf
*/
#ifndef _AASPRINTF_H_
#define _AASPRINTF_H_

#include <Arduino.h>

class AASprintf
{
private:
	size_t fmtbufsize;
	char* fmtbuf;

	size_t allocateFormatBuffer(const size_t size);
	void releaseFormatBuffer();

public:
	AASprintf();
	AASprintf(const size_t);
	~AASprintf();

	void clear();
	void format(const char*, ...);
	void vformat(const char*, va_list);

	operator const char* () const
	{
		return this->fmtbuf;
	}

	operator String() const
	{
		return String(this->fmtbuf);
	}

	const char* c_str() const;
	String toString() const;
};

#endif