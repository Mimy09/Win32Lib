#include "MyWindow.h"

int main() {
	try {
		MyWindow wnd;
		wnd.Create("ConnectFourClass", "Connect 4", RECT{ 0, 0, 800, 600 });
		wnd.Show();


		while (wnd.Run() != TK_MSG_EXIT) {

		}

		return 0;
	}
	catch (tk::Exception e) {
		e.msgWhat();
	}
}