#include <AASprintf.h>

AASprintf::AASprintf() :AASprintf(8)
{
}

AASprintf::AASprintf(const size_t size)
{
	this->fmtbuf = (char*)malloc(size);
	this->fmtbuf[0] = 0x00;
	this->fmtbufsize = size;
}

AASprintf::~AASprintf()
{
	this->releaseFormatBuffer();
}

size_t AASprintf::allocateFormatBuffer(const size_t size)
{
	if (size <= this->fmtbufsize) {
		return size;
	}

	this->releaseFormatBuffer();

	this->fmtbuf = (char*)malloc(size);
	if (this->fmtbuf == NULL) {
		return -1;
	}
	this->fmtbuf[0] = 0x00;
	this->fmtbufsize = size;

	return this->fmtbufsize;
}

void AASprintf::releaseFormatBuffer()
{
	if (this->fmtbuf != NULL) {
		free(this->fmtbuf);
		this->fmtbuf = NULL;
	}
	this->fmtbufsize = 0;
}

void AASprintf::clear()
{
	if ((this->fmtbuf != NULL) && (this->fmtbufsize > 0)) {
		this->fmtbuf[0] = 0x00;
	}
}

void AASprintf::format(const char* fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	this->vformat(fmt, va);
	va_end(va);
}

void AASprintf::vformat(const char* fmt, va_list args)
{
	int totalsize = vsnprintf(this->fmtbuf, this->fmtbufsize, (const char*)fmt, args);
	if ((totalsize + 1) > this->fmtbufsize) {
		this->allocateFormatBuffer(totalsize + 1);
		totalsize = vsnprintf(this->fmtbuf, this->fmtbufsize, (const char*)fmt, args);
	}
}

const char* AASprintf::c_str() const
{
	return this->fmtbuf;
}

String AASprintf::toString() const
{
	return String(this->fmtbuf);
}
