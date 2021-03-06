#pragma once
#include "tkWindow.h"

class MyWindow : public tk::win::Window {
public:
	MyWindow();
	~MyWindow();

	virtual bool OnCreate(HWND hwnd) { 
		return true;
	}
	
	virtual void OnPaint(HDC hdc) {
		SelectObject(hdc, TK_BRUSH_WHITE);
		PatBlt(hdc, 0, 0, ScreenRectWidth(), ScreenRectHeight(), PATCOPY);
		SelectObject(hdc, TK_BRUSH_BLACK);

		/* ---- DEVELOPMENT MODE ----
		Remove for release */
		development_rect = { 10, ScreenRectHeight() - 20, 200, ScreenRectHeight() };
		DrawText(hdc, DEV.data, strlen(DEV.data), &development_rect, DT_LEFT );
		TK_UPDATE_RECT(hwnd(), NULL);
	}

	virtual void Update(double deltaTime) {
		title_rect = { 0, 0, ScreenRectWidth(), 60 };
		Title.SetPosition(title_rect);
		TK_UPDATE_RECT(hwnd(), &title_rect);
		TK_UPDATE_RECT(hwnd(), &development_rect);
	}

private:
	/* -- DEV VAR --*/
	tk::String DEV;
	RECT development_rect;

	/* ---- PRIVATE VARIABLES ---- */
};

MyWindow::MyWindow() {
<<<<<<< HEAD
	
	box_rect = { 150, 10, 250, 110 };
	DEV = "Master";
=======
	DEV = "Development Mode (0.1)";
	title_rect = { 200, 50, 200, 10 };
>>>>>>> master
}

MyWindow::~MyWindow() {
}
