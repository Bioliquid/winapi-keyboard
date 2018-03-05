#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include "langs.h"
#include "char_desc.h"

class iokey {
public:
	iokey();

	void on_message();

	void unhook();
private:
	static void press(wchar_t*);

	static void release();

	static LRESULT CALLBACK KeyboardHook(int, WPARAM, LPARAM);

	static INPUT iokey::ip;
	static langs lang;
	static bool shift;

	HHOOK hook;
	MSG msg;
};