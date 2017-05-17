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

		/* ---- DRAWING ---- */



		/* ---- DEVELOPMENT MODE ----
		Remove for release */
		development_rect = { 10, ScreenRectHeight() - 20, 150, ScreenRectHeight() };
		DrawText(hdc, DEV.data, strlen(DEV.data), &development_rect, DT_LEFT );
		TK_UPDATE_RECT(hwnd(), NULL);
	}

	virtual void Update(double deltaTime) {
		TK_UPDATE_RECT(hwnd(), &box_rect);
		TK_UPDATE_RECT(hwnd(), &development_rect);
	}

private:
	tk::String MousePos, KeyboardKey, DEV;
	RECT development_rect;
	RECT box_rect;
	bool Clicking;
	int mb_click_id;

	tk::win::WinImage _image;
};

MyWindow::MyWindow() {
	
	box_rect = { 150, 10, 250, 110 };
	DEV = "Development Mode";
}

MyWindow::~MyWindow() {
}
