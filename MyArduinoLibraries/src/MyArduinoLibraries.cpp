#include <MyArduinoLibraries.h>
#include <Stopwatch.h>

void halt()
{
	while (1) {
		delay(100);
	}
}

String makeHHMMSS(const time_t* pTime)
{
	struct tm* time = localtime(pTime);
	return makeHHMMSS(time);
}

String makeHHMMSS(const struct tm* const pTM)
{
	char buf[16];
	snprintf(buf, sizeof(buf), "%02d:%02d:%02d"
		, pTM->tm_hour
		, pTM->tm_min
		, pTM->tm_sec
	);
	return String(buf);
}

String makeYYYYMMDD(const time_t* const pTime)
{
	struct tm* time = localtime(pTime);
	return makeYYYYMMDD(time);
}

String makeYYYYMMDD(const struct tm* const timeinfo)
{
	char buf[16];
	snprintf(buf, sizeof(buf), "%04d/%02d/%02d"
		, timeinfo->tm_year + 1900
		, timeinfo->tm_mon + 1
		, timeinfo->tm_mday
	);
	return String(buf);
}

void clearStream(Stream& stream)
{
	while (stream.available() > 0) {
		stream.read();
	}
}

/*
	pTimeoutSec:
		-1=即タイムアウト,0=無限待ち,0<ミリ秒待ち
*/
String stockString = "";
bool readLine(Stream& pStream, String& pString, int pTimeoutSec)
{
	pString.clear();

	String sb = "";
	sb.concat(stockString);
	stockString.clear();

	Stopwatch ReadLineStopwatch = Stopwatch();
	ReadLineStopwatch.restart();
	while (true) {
		if (pStream.available() == 0) {
			// タイムアウトチェック
			bool blTimeout = false;
			if (pTimeoutSec == -1) {
				blTimeout = true;
			} else if (pTimeoutSec > 0) {
				if (ReadLineStopwatch.elapsedMillis() >= (pTimeoutSec * 1000)) {
					blTimeout = true;
				}
			}

			if (blTimeout) {
				stockString.clear();
				stockString.concat(sb);
				return false;
			}

			delay(10);
			continue;
		}

		char c = pStream.read();
		if (c == '\n') {
			continue;
		}
		if (c == '\r') {
			break;
		}

		sb.concat((char)c);
	}

	pString.concat(sb);
	return true;
}

/*
	pItemNo: 0～
*/
String getField(String& pString, const char pSeparator, const int pItemNo)
{
	String result = "";
	int sepaRemain = pItemNo - 1;
	bool blStart = false;
	if (pItemNo == 0) {
		blStart = true;
	}

	for (int i = 0;i < pString.length(); i++) {
		if (pString[i] == pSeparator) {
			if (!blStart) {
				if (sepaRemain > 0) {
					sepaRemain--;
					continue;
				}

				blStart = true;
				continue;
			}

			break;
		}

		if (blStart) {
			result.concat(pString[i]);
		}
	}

	return result;
}

String substring(String& pString, const int pIndex, const int pLength)
{
	return pString.substring(pIndex, pIndex + pLength);
}
