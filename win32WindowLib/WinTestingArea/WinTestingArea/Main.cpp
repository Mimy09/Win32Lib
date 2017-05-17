#include "MyWindow.h"

int main() {
	MyWindow wnd;
	wnd.Create("TEST", "TEST APPLICATION", RECT{ 0, 0, 800, 600 });
	wnd.Show();


	while (wnd.Run() != TK_MSG_EXIT) {
		
	}

	return 0;
}