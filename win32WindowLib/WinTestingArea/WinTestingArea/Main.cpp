#include "MyWindow.h"

int main() {
<<<<<<< HEAD
	MyWindow wnd;
	wnd.Create("Development_class", "Development", RECT{ 0, 0, 800, 600 });
	wnd.Show();
=======
	try {
		MyWindow wnd;
		wnd.Create("ConnectFourClass", "Connect 4", RECT{ 0, 0, 800, 600 });
		wnd.Show();
>>>>>>> ConnectFour


		while (wnd.Run() != TK_MSG_EXIT) {

		}

		return 0;
	}
	catch (tk::Exception e) {
		e.msgWhat();
	}
}