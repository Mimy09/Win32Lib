#pragma once
#include "tkWindow.h"
#include "tkLinkList.h"

class MyWindow : public tk::win::Window {
public:
	MyWindow();
	~MyWindow();

	virtual bool OnCreate(HWND hwnd) {

		//Title.CreateWnd(hwnd, "STATIC", "BULLET HELL", title_rect);
		//Title.SetTextSize(50);

		return true;
	}

	virtual void OnMouseDown(int x, int y, UINT param) {
		if (m_sm.GetState() == tk::GAME_STATE::MENU) {
			m_sm.SetState(new tk::states::GameRunningState());
		}
	}
	
	virtual void OnPaint(HDC hdc) {
		SelectObject(hdc, TK_BRUSH_BLACK);
		PatBlt(hdc, 0, 0, ScreenRectWidth(), ScreenRectHeight(), PATCOPY);
		//SelectObject(hdc, TK_BRUSH_WHITE);

		switch (m_sm.GetState()) {
		case tk::GAME_STATE::MENU:

			/* ---- TITLE ---- */
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(200, 50, 50));
			if (m_title.font == NULL)m_title.SetFont(hdc, 46);
			m_title.Draw(hdc, m_title_string, m_title_rect);

			/* ---- TITLE ---- */
			// SetTextColor(hdc, RGB(255, 255, 255));
			if (m_start.font == NULL)m_start.SetFont(hdc, 46);
			m_start.Draw(hdc, m_start_string, m_start_rect);

			break;
		default:
			break;
		}

		/* ---- DEVELOPMENT MODE ----
		Remove for release */
		SetTextColor(hdc, RGB(255, 255, 255));
		development_rect = { 10, ScreenRectHeight() - 20, 100, ScreenRectHeight() };
		m_development_text.Draw(hdc, m_version, development_rect);
		TK_UPDATE_RECT(hwnd(), NULL);
	}

	virtual void Update(double deltaTime) {
		m_title_rect = { 0, 0, ScreenRectWidth(), 60 };
		TK_UPDATE_RECT(hwnd(), &m_start_rect);
		TK_UPDATE_RECT(hwnd(), &m_title_rect);
		TK_UPDATE_RECT(hwnd(), &development_rect);
	}
	virtual void OnWindowResize() {
		m_title_rect = { 0, 0, ScreenRectWidth(), 60 };
		TK_UPDATE_RECT(hwnd(), &m_start_rect);
		TK_UPDATE_RECT(hwnd(), &m_title_rect);
	}

private:
	/* -- DEV VAR -- */
	tk::win::WinText m_development_text;
	RECT development_rect;

	/* ---- PRIVATE VARIABLES ---- */

	// Title Rect
	RECT m_title_rect;
	tk::String m_title_string;
	tk::win::WinText m_title;

	// Title Rect
	RECT m_start_rect;
	tk::String m_start_string;
	tk::win::WinText m_start;
};

MyWindow::MyWindow() {
	m_title_rect = { 0, 0, ScreenRectWidth(), 60 };
	m_title_string = "BULLET HELL (MENU)";

	m_title_rect = { 0, 300, ScreenRectWidth(), 360 };
	m_start_string = "> START <";
}

MyWindow::~MyWindow() {
}
