#pragma once

#include <windows.h>

bool isAsciiAlpha(int code);
wchar_t* char_to_wchar(char *p);
char trans_char(char c, bool shift);