#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <codecvt>
#include "langs.h"

langs::langs() {
	step = STEP::NONE;
}

void langs::read(const char *lang_file_path) {
	std::wifstream langFile(lang_file_path);
	langFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::wstringstream wss;
	wss << langFile.rdbuf();
	translate_text = wss.str();
}

void langs::parse() {
	std::wstring tmp;
	for (auto el : translate_text) {
		if (el != ' ' && el != '\n' && el != '\t') {
			tmp += el;
		}
	}
	std::wstring sub_text;
	for (auto str_el : tmp) {
		switch (step) {
			case langs::NONE:
				sub_text += str_el;
				if (sub_text == char_to_wchar("LANG_OPTIONS")) {
					step = STEP::OPTIONS;
					sub_text = char_to_wchar("");
				}
				break;
			case langs::OPTIONS:
				sub_text += str_el;
				if (sub_text[0] == '{' && sub_text[sub_text.size() - 1] == '}') {
					parse_option(sub_text);
				}
				break;
			default:
				break;
		}
	}
}

void langs::parse_option(std::wstring s) {
	std::wstring tmp;
	for (auto el : s) {
		if (el == ',' || el == '}') {
			translate_map[tmp[0]] = tmp[tmp.size() - 1];
			tmp = char_to_wchar("");
		}
		else if (el != '{') {
			tmp += el;
		}
	}
}