#pragma once
#include "tkWindow.h"
#include "tkLinkList.h"

class MyWindow : public tk::win::Window {
public:
	MyWindow();
	~MyWindow();

	virtual bool OnCreate(HWND hwnd) { 
		return true;
	}

	virtual void OnMouseDown(int x, int y, UINT param) {
		
	}
	
	virtual void OnPaint(HDC hdc) {
		SelectObject(hdc, TK_BRUSH_WHITE);
		PatBlt(hdc, 0, 0, ScreenRectWidth(), ScreenRectHeight(), PATCOPY);
		SelectObject(hdc, TK_BRUSH_BLACK);

		for (int i = 0; i < 10; i++) {
			
		}

		/* ---- DEVELOPMENT MODE ----
		Remove for release */
		development_rect = { 10, ScreenRectHeight() - 20, 200, ScreenRectHeight() };
		DrawText(hdc, _version.data, strlen(_version.data), &development_rect, DT_LEFT );
		TK_UPDATE_RECT(hwnd(), NULL);
	}

	virtual void Update(double deltaTime) {
		TK_UPDATE_RECT(hwnd(), &development_rect);
	}

private:
	/* -- DEV VAR -- */
	RECT development_rect;

	/* ---- PRIVATE VARIABLES ---- */
	// Title Rect
	RECT title_rect;
	tk::win::WinObject Title;

};

MyWindow::MyWindow() {
	title_rect = { 0, 0, ScreenRectWidth(), 60 };
}

MyWindow::~MyWindow() {
}
