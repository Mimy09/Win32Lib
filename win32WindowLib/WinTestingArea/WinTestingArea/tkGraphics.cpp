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

		gTriangle::gTriangle(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3) {
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
			m_pen = CreatePen(NULL, 0, RGB(255, 255, 255));
		}
		void gTriangle::Draw(HDC hdc, HPEN color) {
			SelectObject(hdc, color);
			if (m_vertex[1].y == m_vertex[2].y) {
				fillBottomFlatTriangle(hdc, m_vertex[0], m_vertex[1], m_vertex[2]);
			}
			else if (m_vertex[0].y == m_vertex[1].y) {
				fillTopFlatTriangle(hdc, m_vertex[0], m_vertex[1], m_vertex[2]);
			}
			else {
				m_vert4 = {
					(float)(m_vertex[0].x + ((float)(m_vertex[1].y - m_vertex[0].y) / (float)(m_vertex[2].y - m_vertex[0].y)) * (m_vertex[2].x - m_vertex[0].x)),
					m_vertex[1].y
				};
				fillBottomFlatTriangle(hdc, m_vertex[0], m_vertex[1], m_vert4);
				fillTopFlatTriangle(hdc, m_vertex[1], m_vert4, m_vertex[2]);
			}
		}
		void gTriangle::DrawLine(HDC hdc, HPEN color) {
			SelectObject(hdc, color);
			MoveToEx(hdc, (int)m_vertex[0].x, (int)m_vertex[0].y, NULL);
			LineTo(hdc, (int)m_vertex[1].x, (int)m_vertex[1].y);

			MoveToEx(hdc, (int)m_vertex[1].x, (int)m_vertex[1].y, NULL);
			LineTo(hdc, (int)m_vertex[2].x, (int)m_vertex[2].y);

			MoveToEx(hdc, (int)m_vertex[2].x, (int)m_vertex[2].y, NULL);
			LineTo(hdc, (int)m_vertex[0].x, (int)m_vertex[0].y);
		}
		void gTriangle::DrawLine(HDC hdc) {
			SelectObject(hdc, m_pen);
			MoveToEx(hdc, (int)m_vertex[0].x, (int)m_vertex[0].y, NULL);
			LineTo(hdc, (int)m_vertex[1].x, (int)m_vertex[1].y);

			MoveToEx(hdc, (int)m_vertex[1].x, (int)m_vertex[1].y, NULL);
			LineTo(hdc, (int)m_vertex[2].x, (int)m_vertex[2].y);

			MoveToEx(hdc, (int)m_vertex[2].x, (int)m_vertex[2].y, NULL);
			LineTo(hdc, (int)m_vertex[0].x, (int)m_vertex[0].y);
		}
		void gTriangle::SetTri(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3) {
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
		}

		void gTriangle::fillBottomFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3) {
			invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
			invslope2 = (v3.x - v1.x) / (v3.y - v1.y);
			curx1 = curx2 = v1.x;

			for (int scanlineY = (int)v1.y; scanlineY < (int)v2.y; scanlineY++) {
				MoveToEx(hdc, (int)curx1, (int)scanlineY, NULL);
				LineTo(hdc, (int)curx2, (int)scanlineY);

				curx1 += invslope1;
				curx2 += invslope2;
			}
		}
		void gTriangle::fillTopFlatTriangle(HDC hdc, math::Vec2 v1, math::Vec2 v2, math::Vec2 v3) {
			invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
			invslope2 = (v3.x - v2.x) / (v3.y - v2.y);
			curx1 = curx2 = v3.x;

			for (int scanlineY = (int)v3.y; scanlineY > (int)v1.y; scanlineY--) {
				MoveToEx(hdc, (int)curx1, (int)scanlineY, NULL);
				LineTo(hdc, (int)curx2, (int)scanlineY);

				curx1 -= invslope1;
				curx2 -= invslope2;
			}
		}

		gTriangle::~gTriangle() { DeleteObject(m_pen); }

		/************************************************************************************************************************
		************************************************************************************************************************/

		gRectange::gRectange(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3, math::Vec2 v4) {
			tri_0 = {
				tk::math::Vec2{ v1.x, v1.y },
				tk::math::Vec2{ v2.x, v2.y },
				tk::math::Vec2{ v3.x, v3.y }
			};
			tri_1 = {
				tk::math::Vec2{ v1.x, v1.y },
				tk::math::Vec2{ v4.x, v4.y },
				tk::math::Vec2{ v3.x, v3.y }
			};
			m_pen = CreatePen(NULL, 0, RGB(255, 255, 255));
		}

		void gRectange::SetRect(math::Vec2 v1, math::Vec2 v2, math::Vec2 v3, math::Vec2 v4) {
			tri_0.SetTri(
				tk::math::Vec2{ v1.x, v1.y },
				tk::math::Vec2{ v2.x, v2.y },
				tk::math::Vec2{ v3.x, v3.y }
			);

			tri_1.SetTri(
				tk::math::Vec2{ v1.x, v1.y },
				tk::math::Vec2{ v4.x, v4.y },
				tk::math::Vec2{ v3.x, v3.y }
			);
		}

		void gRectange::Draw(HDC hdc, HPEN color) {
			SelectObject(hdc, color);
			tri_0.Draw(hdc, color);
			tri_1.Draw(hdc, color);
		}

		void gRectange::DrawLine(HDC hdc, HPEN color) {
			SelectObject(hdc, color);
			tri_0.DrawLine(hdc, color);
			tri_1.DrawLine(hdc, color);
		}
		void gRectange::DrawLine(HDC hdc) {
			tri_0.DrawLine(hdc);
			tri_1.DrawLine(hdc);
		}

		gRectange::~gRectange() {
			DeleteObject(m_pen);
		}

		/************************************************************************************************************************
		************************************************************************************************************************/
	}
}