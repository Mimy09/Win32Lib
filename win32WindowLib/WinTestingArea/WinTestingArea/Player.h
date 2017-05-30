#pragma once
#include <Windows.h>
#include "tkWindow.h"

class Player {
public:
	Player();
	Player(float x, float y, float width, float height);
	~Player();

	void Draw(HDC hdc);
	void Update(double deltaTime, float screenW, float screenH);
	void OnKeyUp(UINT key);
	void OnKeyDown(UINT key);

	inline tk::win::Rect rect() { return ply_rect; }
private:
	tk::win::Rect ply_rect;
	bool ply_forward, ply_back, ply_left, ply_right;
};