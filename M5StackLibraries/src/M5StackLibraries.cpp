#include <M5StackLibraries.h>

void cls()
{
	M5.Lcd.clear();
	M5.Lcd.setCursor(0, 0);
}

void beep(int millis)
{
	M5.Speaker.beep();
	delay(millis);
	M5.Speaker.mute();
}

void clearRight(const uint16_t color)
{
	int x = M5.Lcd.getCursorX();
	int y = M5.Lcd.getCursorY();
	int w = M5.lcd.width();
	int h = M5.lcd.fontHeight();
	M5.Lcd.fillRect(x, y, w, h, color);
}
