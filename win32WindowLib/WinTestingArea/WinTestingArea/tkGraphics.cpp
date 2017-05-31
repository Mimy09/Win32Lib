#include "tkGraphics.h"
#include "tkMath.h"

namespace tk {
	namespace graphics {
		/************************************************************************************************************************
		************************************************************************************************************************/

		Rect Rect::area() { return Rect(x, y, x + width, y + height); }
		RECT Rect::convertRECT() { return RECT{ (long)x,(long)y, (long)width, (long)height }; }

		/************************************************************************************************************************
		************************************************************************************************************************/
		Triangle::Triangle(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3) {
			m_vertex[0] = v1;
			m_vertex[1] = v2;
			m_vertex[2] = v3;
			math::Vec2 m_vertex_temp = {};

			for (int i = 1; i<3; ++i) {
				for (int j = 0; j < (3 - i); ++j) {
					if (m_vertex[j].y > m_vertex[j + 1].y) {
						m_vertex_temp = m_vertex[j];
						m_vertex[j] = m_vertex[j + 1];
						m_vertex[j + 1] = m_vertex_temp;
					}
				}
			}
			m_vert4 = {
				(float)(m_vertex[0].x + ((float)(m_vertex[1].y - m_vertex[0].y) / (float)(m_vertex[2].y - m_vertex[0].y)) * (m_vertex[2].x - m_vertex[0].x)),
				m_vertex[1].y
			};

			hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		}
		void Triangle::DrawTri(HDC hdc) {
			SelectObject(hdc, hPen);

			fillBottomFlatTriangle(hdc, m_vertex[0], m_vertex[1], m_vert4);
			fillTopFlatTriangle(hdc, m_vertex[1], m_vert4, m_vertex[2]);
		}

		void Triangle::fillBottomFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3) {
			float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
			float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

			float curx1 = v1.x;
			float curx2 = v1.x;

			for (int scanlineY = v1.y; scanlineY < v2.y; scanlineY++) {

				MoveToEx(hdc, curx1, scanlineY, NULL);
				LineTo(hdc, curx2, scanlineY);

				curx1 += invslope1;
				curx2 += invslope2;
			}
		}
		void Triangle::fillTopFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3) {
			float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
			float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

			float curx1 = v3.x;
			float curx2 = v3.x;

			for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--) {

				MoveToEx(hdc, curx1, scanlineY, NULL);
				LineTo(hdc, curx2, scanlineY);

				curx1 -= invslope1;
				curx2 -= invslope2;
			}
		}

		/************************************************************************************************************************
		************************************************************************************************************************/
	}
}