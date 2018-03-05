#include <iostream>
#include <windows.h>
#include "iokey.h"
#include <string>
#include "langs.h"
using namespace std;

int main() {
	iokey k;

	k.on_message();
	k.unhook();
}