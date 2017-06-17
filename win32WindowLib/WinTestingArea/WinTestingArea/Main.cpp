#include "MyWindow.h"

int main() {
	try {
		MyWindow wnd;
		wnd.Create("Game_f0h3gh37", "Game", RECT{ 0, 0, 800, 600 });
		wnd.Show();
		wnd.RunWindow();
		return 0;
	} catch (tk::Exception e) {
		e.msgWhat();
	}
}