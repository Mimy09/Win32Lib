#pragma once
#include <tkWindow.h>
#include <tkLinkList.h>
#include "tkStateManager.h"
#include "tkGraphics.h"
#include "tkHashMap.h"
#include "Player.h"
#include "EnemyFactory.h"

#include "tkTree.h"

class MyWindow : public tk::win::Window {
public:
	MyWindow();
	~MyWindow();

<<<<<<< HEAD
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
=======
	virtual void OnKeyDown(UINT key);
	virtual void OnKeyUp(UINT key);
	virtual void OnMouseDown(int x, int y, UINT param);
	virtual void OnPaint(HDC hdc);

	virtual void Update(double deltaTime);
	virtual void OnWindowResize();

	void Menu(HDC hdc);
	void Options(HDC hdc);
	void Game(HDC hdc);
	void SplashScreen(HDC hdc);
>>>>>>> BulletHell

private:
	tk::states::StateManager m_sm;

	/* -- DEV VAR -- */
	tk::win::WinText m_development_text;
	RECT development_rect;
	

	/* ---- PRIVATE VARIABLES ---- */
<<<<<<< HEAD
	// Title Rect
	RECT title_rect;
	tk::win::WinObject Title;

};
=======
	// Title Text
	RECT m_title_rect;
	tk::String m_title_string;
	tk::win::WinText m_title;

	// Start Text
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

	double m_deltaTime;

	/* ---- Game Stuff ---- */
	Player ply;
	//tk::math::Mat3 mat;
	//tk::math::Vec3 v1;
	//tk::math::Vec3 v2;
	//tk::math::Vec3 v3;
	//tk::math::Vec3 v4;

	game::Enemy* m_enemy;
	game::Enemy* m_enemy1;

	int m_score;
>>>>>>> BulletHell

	tk::std::LinkList<game::Enemy*> m_enemys;

	/* ---- TESTING ---- */
	tk::graphics::gRectange rect_1;
	tk::String comp_stats;
	game::EnemyFactory m_enemyFactory;
	tk::std::Tree<int> tree;
};