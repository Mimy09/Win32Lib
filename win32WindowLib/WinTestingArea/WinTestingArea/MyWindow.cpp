#include "MyWindow.h"

MyWindow::MyWindow() {
	m_sm.SetState(new tk::states::InitState());

	m_title_string = "SPACE GAME";
	m_start_string = "START";
	m_options_string = "OPTIONS";
	m_exit_string = "EXIT";

	m_title.SetFont(72);
	m_start.SetFont(46);
	m_options.SetFont(46);
	m_exit.SetFont(46);

	m_score = 0;
	m_deltaTime = 0;
	comp_stats = "";
	m_enemys.InsertEnd(m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY));

	m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
	m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
	m_enemy1->rect() = tk::graphics::Rect(75, 75, 100, 100);
	//tri = { tk::math::Vec2{10, 10}, tk::math::Vec2{ 200, 10 }, tk::math::Vec2{ 10,200 } };
	//tri2 = { tk::math::Vec2{ 200, 10 }, tk::math::Vec2{ 10, 200 }, tk::math::Vec2{ 200, 200 } };


	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);
	tree.DeleteNode(4);

	int k = 0;
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
	case tk::states::GAME_STATE::SPLASHSCREEN: break;
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
	case tk::states::GAME_STATE::SPLASHSCREEN: break;
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
	case tk::states::GAME_STATE::SPLASHSCREEN: SplashScreen(hdc); break;
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
	Window::Update(deltaTime);
	m_deltaTime = deltaTime;
	m_sm.Update();

	m_timer.calcFPS();

	switch (m_sm.GetState()) {
	case tk::states::GAME_STATE::INIT: m_sm.SetState(new tk::states::SplashScreenState()); break;
	case tk::states::GAME_STATE::SPLASHSCREEN:
		m_title_rect = { 0, ScreenRectHeight() / 2 - 60, ScreenRectWidth(), 60 };
		if (m_timer.elapsed() > 3) {
			m_sm.SetState(new tk::states::MenuState);
		}
		break;
	case tk::states::GAME_STATE::GAME_RUNNING:
		ply.Update();
		ply.UpdatePlayer(deltaTime, ScreenRectWidth(), ScreenRectHeight());
		m_enemy->Update();
		m_enemy->UpdateEnemy(ply, deltaTime);
		m_enemy1->Update();
		if (tk::graphics::Rect::IntersectBox(m_enemy1->rect().area().convertRECT(), ply.rect().area().convertRECT())) {
			if (m_enemy->Health() > 0) m_enemy->Health(m_enemy->Health() - (10 * (float)deltaTime));
		}
		//m_enemy1->UpdateEnemy(ply, deltaTime);
		break;
	case tk::states::GAME_STATE::MENU:
		m_title_rect = { 0, 50, ScreenRectWidth(), 60 };
		m_exit_rect = { 0, 400, ScreenRectWidth(), 460 };
		m_start_rect = { 0, 200, ScreenRectWidth(), 260 };
		m_options_rect = { 0, 300, ScreenRectWidth(), 360 };
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
	} TK_UPDATE_RECT(hwnd(), NULL);
}

void MyWindow::OnWindowResize() {
	switch (m_sm.GetState()) {
	case tk::states::GAME_STATE::GAME_RUNNING: break;
	case tk::states::GAME_STATE::MENU:
		m_title_rect = { 0, 50, ScreenRectWidth(), 60 };
		m_exit_rect = { 0, 400, ScreenRectWidth(), 60 };
		m_start_rect = { 0, 200, ScreenRectWidth(), 60 };
		m_options_rect = { 0, 300, ScreenRectWidth(), 60 };
		break;
	case tk::states::GAME_STATE::OPTIONS: break;
	case tk::states::GAME_STATE::CLOSING: break;
	default: break;
	} TK_UPDATE_RECT(hwnd(), NULL);
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

	comp_stats = (tk::String)"   FPS: " + m_timer.GetFPS();
	comp_stats += (tk::String)"   DT: " + m_deltaTime;
	TextOut(hdc, 10, 10, comp_stats.data, comp_stats.length());
}

void MyWindow::Options(HDC hdc) {
	comp_stats = (tk::String)"   FPS: " + m_timer.GetFPS();
	comp_stats += (tk::String)"   DT: " + m_deltaTime;
	TextOut(hdc, 10, 10, comp_stats.data, comp_stats.length());
}

void MyWindow::Game(HDC hdc) {
	m_enemy1->Draw(hdc, TK_PEN_BLUE);
	m_enemy->Draw(hdc, TK_PEN_RED);
	ply.Draw(hdc, TK_PEN_GREEN);

	if (ply.Health() <= 0) {
		ply.Reset();
		m_sm.SetState(new tk::states::MenuState());
	}

	if (m_enemy != nullptr) {
		if (m_enemy->Health() <= 0) {
			m_score++;
			ply.Fuel() += 10;
			ply.Health(ply.Health() + 25);
			if (m_enemy) {
				delete m_enemy;
				m_enemy = nullptr;
			}
			if (m_enemy1) {
				delete m_enemy1;
				m_enemy1 = nullptr;
			}
			int i = (int)(rand() % 3);
			switch (i) {
			case 1:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY); break;
			case 2:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::MEDIUM);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::MEDIUM); break;
			case 3:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::HARD);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::HARD); break;
			default:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY); break;
			}
			int randX = rand() % 750, randY = rand() % 550;
			m_enemy1->rect() = tk::graphics::Rect(randX - 25, randY - 25, 100, 100 );
			m_enemy->rect() = tk::graphics::Rect(randX, randY, 50, 50 );
		}
	}

	tk::String k = "", ply_score = "", enemy_stats = "", ply_stats = "";
	comp_stats = (tk::String)"   FPS: " + m_timer.GetFPS();
	comp_stats += (tk::String)"   DT: " + m_deltaTime;
	k += (tk::String)"   x: " + ply.rect().x;
	k += (tk::String)"   y: " + ply.rect().y;
	k += (tk::String)"   Y_vel: " + ply.m_vel_y;
	k += (tk::String)"   X_vel: " + ply.m_vel_x;
	ply_score += (tk::String)"   Score: " + m_score;
	ply_score += (tk::String)"   Fuel: " + ply.Fuel();
	enemy_stats += (tk::String)"   Time: " + (int)m_enemy->Health();
	ply_stats += (tk::String)"   Food: " + (int)ply.Health();
	TextOut(hdc, 10, 10, comp_stats.data, comp_stats.length());
	TextOut(hdc, 10, 30, k.data, k.length());
	TextOut(hdc, 10, 50, ply_score.data, ply_score.length());
	TextOut(hdc, m_enemy->rect().x, m_enemy->rect().y, enemy_stats.data, enemy_stats.length());
	TextOut(hdc, ply.rect().x, ply.rect().y, ply_stats.data, ply_stats.length());
}

void MyWindow::SplashScreen(HDC hdc) {
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(200, 50, 50));
	m_title.Draw(hdc, m_title_string, m_title_rect);
	SetTextColor(hdc, RGB(255, 255, 255));

	comp_stats = (tk::String)"   FPS: " + m_timer.GetFPS();
	comp_stats += (tk::String)"   DT: " + m_deltaTime;
	TextOut(hdc, 10, 10, comp_stats.data, comp_stats.length());
}
