#include "MyWindow.h"

MyWindow::MyWindow() {
	m_sm.SetState(new tk::states::MenuState());

	m_title_string = "BULLET HELL";
	m_start_string = "START";
	m_options_string = "OPTIONS";
	m_exit_string = "EXIT";

	m_title.SetFont(72);
	m_start.SetFont(46);
	m_options.SetFont(46);
	m_exit.SetFont(46);

	m_enemys.InsertEnd(m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY));

	m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);

	//tri = { tk::math::Vec2{10, 10}, tk::math::Vec2{ 200, 10 }, tk::math::Vec2{ 10,200 } };
	//tri2 = { tk::math::Vec2{ 200, 10 }, tk::math::Vec2{ 10, 200 }, tk::math::Vec2{ 200, 200 } };
}
MyWindow::~MyWindow() {
	if (m_enemy) {
		delete m_enemy;
		m_enemy = nullptr;
	}
}

void MyWindow::OnKeyDown(UINT key) {
	if (key == VK_ESCAPE) {
		ply.Reset();
		m_sm.SetState(new tk::states::MenuState());
	}
	switch (m_sm.GetState()) {
	case tk::states::GAME_STATE::GAME_RUNNING:
	{
		ply.OnKeyDown(key);
		break;
	}
	case tk::states::GAME_STATE::MENU: break;
	case tk::states::GAME_STATE::OPTIONS: break;
	case tk::states::GAME_STATE::CLOSING: break;
	default: break;
	}
}
void MyWindow::OnKeyUp(UINT key) {
	switch (m_sm.GetState()) {
	case tk::states::GAME_STATE::GAME_RUNNING:
	{
		ply.OnKeyUp(key);
		break;
	}
	case tk::states::GAME_STATE::MENU: break;
	case tk::states::GAME_STATE::OPTIONS: break;
	case tk::states::GAME_STATE::CLOSING: break;
	default: break;
	}
}

void MyWindow::OnMouseDown(int x, int y, UINT param) {
	if (m_sm.GetState() == tk::states::GAME_STATE::MENU) {
		RECT mousePos = { x - 1, y - 1, x + 1, y + 1 };
		if (tk::graphics::Rect::IntersectBox(mousePos, m_start_rect)) {
			m_sm.SetState(new tk::states::GameRunningState());
		}
		if (tk::graphics::Rect::IntersectBox(mousePos, m_options_rect)) {
			m_sm.SetState(new tk::states::OptionsState());
		}
		if (tk::graphics::Rect::IntersectBox(mousePos, m_exit_rect)) {
			m_sm.SetState(new tk::states::ClosingState());
			PostQuitMessage(0);
		}
	}
}
void MyWindow::OnPaint(HDC hdc) {
	SelectObject(hdc, TK_BRUSH_BLACK);
	PatBlt(hdc, 0, 0, ScreenRectWidth(), ScreenRectHeight(), PATCOPY);
	SelectObject(hdc, TK_BRUSH_WHITE);

	switch (m_sm.GetState()) {
	case tk::states::GAME_STATE::GAME_RUNNING: Game(hdc); break;
	case tk::states::GAME_STATE::MENU: Menu(hdc); break;
	case tk::states::GAME_STATE::OPTIONS: Options(hdc); break;
	case tk::states::GAME_STATE::CLOSING: break;
	default: break;
	}

	/* ---- DEVELOPMENT MODE ----
	Remove for release */
	SetTextColor(hdc, RGB(255, 255, 255));
	development_rect = { 10, ScreenRectHeight() - 20, 100, ScreenRectHeight() };
	m_development_text.Draw(hdc, m_version, development_rect);
	TK_UPDATE_RECT(hwnd(), NULL);
}

void MyWindow::Update(double deltaTime) {
	m_sm.Update();
	switch (m_sm.GetState()) {
	case tk::states::GAME_STATE::GAME_RUNNING:
		ply.Update();
		ply.UpdatePlayer(deltaTime, ScreenRectWidth(), ScreenRectHeight());
		m_enemy->Update();
		m_enemy->UpdateEnemy(ply);
		TK_UPDATE_RECT(hwnd(), &ply.rect().area().convertRECT());
		TK_UPDATE_RECT(hwnd(), &m_enemy->rect().area().convertRECT());
		break;
	case tk::states::GAME_STATE::MENU:
		m_title_rect = { 0, 50, ScreenRectWidth(), 60 };
		m_exit_rect = { 0, 400, ScreenRectWidth(), 460 };
		m_start_rect = { 0, 200, ScreenRectWidth(), 260 };
		m_options_rect = { 0, 300, ScreenRectWidth(), 360 };
		TK_UPDATE_RECT(hwnd(), &m_exit_rect);
		TK_UPDATE_RECT(hwnd(), &m_start_rect);
		TK_UPDATE_RECT(hwnd(), &m_title_rect);
		TK_UPDATE_RECT(hwnd(), &m_options_rect);
		break;
	case tk::states::GAME_STATE::OPTIONS:
	{
		/*v1 = mat * tk::math::Vec3{ -100, -100, 1 };
		v2 = mat * tk::math::Vec3{ 100, -100, 1 };
		v3 = mat * tk::math::Vec3{ 100,  100, 1 };
		v4 = mat * tk::math::Vec3{ -100,  100, 1 };

		mat.SetRotateZ(m_timer.elapsed() / 10);
		rect_1 = {
			tk::math::Vec2{ v1.x + ScreenRectWidth() / 2, v1.y + ScreenRectHeight() / 2 },
			tk::math::Vec2{ v2.x + ScreenRectWidth() / 2, v2.y + ScreenRectHeight() / 2 },
			tk::math::Vec2{ v3.x + ScreenRectWidth() / 2, v3.y + ScreenRectHeight() / 2 },
			tk::math::Vec2{ v4.x + ScreenRectWidth() / 2, v4.y + ScreenRectHeight() / 2 }
		};*/
		break;
	}
	case tk::states::GAME_STATE::CLOSING: break;
	default: break;
	} TK_UPDATE_RECT(hwnd(), &development_rect);
}

void MyWindow::OnWindowResize() {
	switch (m_sm.GetState()) {
	case tk::states::GAME_STATE::GAME_RUNNING:
		TK_UPDATE_RECT(hwnd(), &ply.rect().area().convertRECT());
		break;
	case tk::states::GAME_STATE::MENU:
		m_title_rect = { 0, 50, ScreenRectWidth(), 60 };
		m_exit_rect = { 0, 400, ScreenRectWidth(), 60 };
		m_start_rect = { 0, 200, ScreenRectWidth(), 60 };
		m_options_rect = { 0, 300, ScreenRectWidth(), 60 };
		TK_UPDATE_RECT(hwnd(), &m_exit_rect);
		TK_UPDATE_RECT(hwnd(), &m_start_rect);
		TK_UPDATE_RECT(hwnd(), &m_title_rect);
		TK_UPDATE_RECT(hwnd(), &m_options_rect);
		break;
	case tk::states::GAME_STATE::OPTIONS: break;
	case tk::states::GAME_STATE::CLOSING: break;
	default: break;
	}
}

void MyWindow::Menu(HDC hdc) {
	SetBkMode(hdc, TRANSPARENT);

	/* ---- TITLE ---- */
	SetTextColor(hdc, RGB(200, 50, 50));
	m_title.Draw(hdc, m_title_string, m_title_rect);

	/* ---- START ---- */
	SetTextColor(hdc, RGB(255, 255, 255));
	m_start.Draw(hdc, m_start_string, m_start_rect);

	/* ---- OPTIONS ---- */
	m_options.Draw(hdc, m_options_string, m_options_rect);

	/* ---- EXIT ---- */
	m_exit.Draw(hdc, m_exit_string, m_exit_rect);
}

void MyWindow::Options(HDC hdc) {
	
}

void MyWindow::Game(HDC hdc) {
	m_enemy->Draw(hdc, TK_PEN_RED);
	ply.Draw(hdc, TK_PEN_GREEN);
	if (ply.Health() == 0) {m_sm.SetState(new tk::states::MenuState()); }

	tk::String k = "", ply_stats = "";
	k += (tk::String)"   x: " + ply.rect().x;
	k += (tk::String)"   y: " + ply.rect().y;
	k += (tk::String)"   Y_vel: " + ply.m_vel_y;
	k += (tk::String)"   X_vel: " + ply.m_vel_x;
	ply_stats += (tk::String)"   Health: " + ply.Health();
	TextOut(hdc, 10, 10, k.data, k.length());
	TextOut(hdc, 10, 30, ply_stats.data, ply_stats.length());
}
