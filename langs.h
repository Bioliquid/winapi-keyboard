#pragma once

#include <map>
#include <windows.h>
#include "char_desc.h"

class langs {
public:
	langs();

	void read(const char *);
	void parse();

	std::map<char, wchar_t> translate_map;
private:
	void parse_option(std::wstring);

	enum STEP { NONE, OPTIONS };

	STEP step;

	std::wstring translate_text;
};