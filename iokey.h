#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include "langs.h"

class iokey {
public:
	iokey();

	static void press(wchar_t*);
	static void press_special(int);
	static void release();

	static wchar_t* char_to_wchar(char *);

	void unhook();
	MSG msg;
private:

	static LRESULT CALLBACK KeyboardHook(int, WPARAM, LPARAM);

	static char trans_char(char, bool);
	static bool isAsciiAlpha(int code);

	HHOOK hook;
	static INPUT iokey::ip;

	static langs lang;

	static bool shift;
};