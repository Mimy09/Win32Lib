#pragma once
#include "tkWindow.h"
#include "tkLinkList.h"

class MyWindow : public tk::win::Window {
public:
	MyWindow();
	~MyWindow();

	bool IntersectBox(RECT r1, RECT r2);

	virtual void OnKeyDown(UINT key);
	virtual void OnMouseDown(int x, int y, UINT param);
	virtual void OnPaint(HDC hdc);

	virtual void Update(double deltaTime);
	virtual void OnWindowResize();

	void Menu(HDC hdc);
	void Options(HDC hdc);
	void Game(HDC hdc);

private:
	/* -- DEV VAR -- */
	tk::win::WinText m_development_text;
	RECT development_rect;

	/* ---- PRIVATE VARIABLES ---- */
	

	// Title Text
	RECT m_title_rect;
	tk::String m_title_string;
	tk::win::WinText m_title;

	// Title Text
	RECT m_start_rect;
	tk::String m_start_string;
	tk::win::WinText m_start;

	// Options Text
	RECT m_options_rect;
	tk::String m_options_string;
	tk::win::WinText m_options;

	// Exit Text
	RECT m_exit_rect;
	tk::String m_exit_string;
	tk::win::WinText m_exit;

};

