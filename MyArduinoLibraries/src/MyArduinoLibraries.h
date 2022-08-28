/*
My Arduino Libraries
*/
#ifndef _MYARDUINOLIBRARIES_H_
#define _MYARDUINOLIBRARIES_H_

#include <Arduino.h>

extern void halt();
extern String makeHHMMSS(const time_t*);
extern String makeHHMMSS(const struct tm* const);
extern String makeYYYYMMDD(const time_t* const);
extern String makeYYYYMMDD(const struct tm* const);
extern void clearStream(Stream&);
extern bool readLine(Stream& pStream, String& pString, int pTimeoutSec = 5);
extern String getField(String& pString, const char pSeparator, const int pItemNo);
extern String substring(String& pString, const int pIndex, const int pLength);
#endif