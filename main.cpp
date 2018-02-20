#include <iostream>
#include <windows.h>
#include "iokey.h"
#include <string>
#include "langs.h"
using namespace std;

int main() {
	iokey k;

	while (!GetMessage(&k.msg, NULL, 0, 0)) {
		TranslateMessage(&k.msg);
		DispatchMessage(&k.msg);
	}
	k.unhook();

	system("pause");
}