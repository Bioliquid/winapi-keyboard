#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <codecvt>
#include <map>
using namespace std;

class langs {
public:

	langs();

	void read(const char *);
	void parse();

	map<char, wchar_t> translate_map;
private:
	void parse_option(wstring);

	enum STEP { NONE, OPTIONS };

	STEP step;

	wstring translate_text;
};