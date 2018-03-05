#include "char_desc.h"

bool isAsciiAlpha(int code) {
	return (code >= 0 && code <= 127 && isalpha(char(code)));
}

wchar_t* char_to_wchar(char *p) {
	WCHAR *pwcsName;
	int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
	pwcsName = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)pwcsName, nChars);
	return pwcsName;
}

char trans_char(char c, bool shift) {
	if (shift == true) {
		return toupper(c);
	}
	return tolower(c);
}