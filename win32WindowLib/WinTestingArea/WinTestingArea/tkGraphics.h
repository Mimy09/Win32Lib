#pragma once
#include <Windows.h>
#include "tkMath.h"

namespace tk {
	namespace graphics {
		/************************************************************************************************************************
		************************************************************************************************************************/
		
		struct Rect {
			Rect() {}
			Rect(double posX, double posY, double posWidth, double posheight)
				: x(posX), y(posY), width(posWidth), height(posheight) {
			}
			Rect area();
			RECT convertRECT();
			double x, y, width, height;
		};

		/************************************************************************************************************************
		************************************************************************************************************************/

		struct Triangle {
			Triangle() {}
			Triangle(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3);

			void DrawTri(HDC hdc);
			void fillBottomFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3);
			void fillTopFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3);

		private:
			math::Vec2 m_vertex[3];
			math::Vec2 m_vert4;
			HPEN hPen;

		};

		/************************************************************************************************************************
		************************************************************************************************************************/
	}
}