#pragma once
#include <Windows.h>
#include "tkMath.h"

namespace tk {
	namespace graphics {
		/************************************************************************************************************************
		************************************************************************************************************************/
		
		struct Rect {
			Rect area();
			RECT convertRECT();
			float x, y, width, height;

			Rect() {}
			Rect(float posX, float posY, float posWidth, float posheight)
				: x(posX), y(posY), width(posWidth), height(posheight) {
			}

			static bool IntersectBox(RECT r1, RECT r2) {
				/*if (r1.left > r2.left &&
					r1.right < (r2.right + r2.left) &&
					r1.top > r2.top &&
					r1.bottom < (r2.bottom + r2.top)) {
					return true;
				}return false;*/
				
				if (r1.bottom < r2.top) return false;
				if (r1.top > r2.bottom) return false;
				if (r1.right < r2.left) return false;
				if (r1.left > r2.right) return false;
				return true;

			}
		};

		/************************************************************************************************************************
		************************************************************************************************************************/

		struct gTriangle {
			gTriangle() {}
			~gTriangle();
			gTriangle(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3);

			void Draw(HDC hdc, HPEN color);
			void DrawLine(HDC hdc, HPEN color);
			void DrawLine(HDC hdc);


			void SetTri(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3);
		private:
			math::Vec2 m_vertex[3];
			math::Vec2 m_vert4;
			HPEN m_pen;

			float invslope1, invslope2;

			float curx1, curx2;

			void fillBottomFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3);
			void fillTopFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3);
		};

		/************************************************************************************************************************
		************************************************************************************************************************/

		struct gRectange {
			gRectange() {}
			~gRectange();
			gRectange(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3, math::Vec2 v4);

			void SetRect(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3, math::Vec2 v4);
			void Draw(HDC hdc, HPEN color);
			void DrawLine(HDC hdc, HPEN color);
			void DrawLine(HDC hdc);


		private:
			gTriangle tri_0, tri_1;
			HPEN m_pen;
		};

		/************************************************************************************************************************
		************************************************************************************************************************/

		
	}
}