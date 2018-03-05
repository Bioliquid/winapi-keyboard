#include "iokey.h"

INPUT iokey::ip;
bool iokey::shift;
langs iokey::lang;

LRESULT CALLBACK iokey::KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
	bool letter = true;
	static int last = 0;
	if (nCode == HC_ACTION) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		int code = p->vkCode;

		if (wParam == WM_KEYDOWN) {
			if (code == 0xA2) {
				last = code;
				return CallNextHookEx(NULL, nCode, wParam, lParam);
			}
			if (last == 0xA2) {
				letter = false;
			}
			if (code == 0xA0 || code == 0xA1) {
				letter = false;
				shift = true;
			}
			if (letter == true && isAsciiAlpha(code)) {
				char ct = trans_char(char(code), shift);
				char *p = new char(ct);
				wchar_t *pwcsName = char_to_wchar(p);
				if (lang.translate_map.find(*pwcsName) != lang.translate_map.end()) {
					pwcsName = new wchar_t(lang.translate_map[ct]);
				}

				iokey::press(pwcsName);
				iokey::release();

				return 1;
			}
		} else if (wParam == WM_KEYUP) {
			if (code == 0xA0 || code == 0xA1) {
				letter = 0;
				shift = false;
			}
			if (code == 0xA2) {
				last = 0;
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

iokey::iokey() {
	lang.read("lang.txt");
	lang.parse();

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, 0, 0);
}

void iokey::press(wchar_t *key) {
	ip.ki.dwFlags = KEYEVENTF_UNICODE;
	ip.ki.wVk = 0;
	ip.ki.wScan = *key;
	SendInput(1, &ip, sizeof(INPUT));
}

void iokey::release() {
	ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void iokey::on_message() {
	while (!GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void iokey::unhook() {
	UnhookWindowsHookEx(hook);
}