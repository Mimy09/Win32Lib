#include "tkWinObjects.h"
namespace tk {
	namespace win {	
		
		/************************************************************************************************************************
		************************************************************************************************************************/

		WinObject::WinObject() { _hwnd = nullptr; }

		WinObject::WinObject(HWND hwnd, tk::String classType, tk::String text, RECT rect) {
			HWND hwndObject = CreateWindow(
				classType.data, text.data,
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				rect.left, rect.top,
				rect.left + rect.right,
				rect.top + rect.bottom,
				hwnd,
				NULL,
				GetModuleHandle(NULL),
				NULL
			); _hwnd = hwndObject;
		}

		void WinObject::CreateWnd(HWND hwnd, tk::String classType, tk::String text, RECT rect) {
			HWND hwndObject = CreateWindow(
				classType.data, text.data,
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				rect.left, rect.top,
				rect.left + rect.right,
				rect.top + rect.bottom,
				hwnd,
				NULL,
				GetModuleHandle(NULL),
				NULL
			); _hwnd = hwndObject;
		}

		void WinObject::SetTextSize(int Size) {
			HFONT hFont = CreateFont(
				Size, 0, 0, 0,
				FW_DONTCARE,
				FALSE, FALSE, FALSE,
				ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				"Arial"
			);
			SendMessage(_hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		}

		void WinObject::SetPosition(RECT rect) {
			MoveWindow(
				_hwnd,
				rect.left, rect.top,
				rect.right, rect.bottom,
				true
			);
		}
		HWND WinObject::hwnd() { return _hwnd; }

		/************************************************************************************************************************
		************************************************************************************************************************/

		WinImage::WinImage() {
			bmpSource = NULL;
			hdcSource = NULL;
		}

		void WinImage::Load(tk::String file) {
			bmpSource = (HBITMAP)LoadImage(NULL, file.data, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			hdcSource = CreateCompatibleDC(GetDC(0));
		}

		void WinImage::Select() { SelectObject(hdcSource, bmpSource); }

		void WinImage::Draw(HDC hdc, RECT rect) {
			BitBlt(
				hdc,
				rect.left, rect.top,
				rect.right, rect.bottom,
				hdcSource, 0, 0, SRCCOPY
			);
		}

		/************************************************************************************************************************
		************************************************************************************************************************/

		WinText::WinText() {
			font = NULL;
			hFontOld = NULL;
		}
		WinText::WinText(HDC hdc, tk::String Text, RECT Position) {
			pos = {
				Position.left, Position.top,
				Position.left + Position.right,
				Position.top + Position.bottom
			};
			SelectObject(hdc, font);
			DrawText(hdc, Text.data, strlen(Text.data), &pos, DT_CENTER);
			SelectObject(hdc, hFontOld);
		}
		void WinText::Draw(HDC hdc, tk::String Text, RECT Position) {
			if (hFontOld == NULL)hFontOld = (HFONT)SelectObject(hdc, font);
			pos = {
				Position.left, Position.top,
				Position.left + Position.right,
				Position.top + Position.bottom
			};
			if (font) SelectObject(hdc, font);
			DrawText(hdc, Text.data, strlen(Text.data), &pos, DT_CENTER);
			if (hFontOld) SelectObject(hdc, hFontOld);
		}
		void WinText::SetFont(int size) {
			font = CreateFont(
				size, 0, 0, 0,
				FW_DONTCARE,
				FALSE, FALSE, FALSE,
				ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				"Arial"
			);
		}

		/************************************************************************************************************************
		************************************************************************************************************************/

		Rect Rect::area() { return Rect(x, y, x + width, y + height); }
		RECT Rect::convertRECT() { return RECT{ (long)x,(long)y, (long)width, (long)height }; }

		/************************************************************************************************************************
		************************************************************************************************************************/
		Triangle::Triangle(Vec2 v1, Vec2 v2, Vec2 v3) {
			m_vertex[0] = v1;
			m_vertex[1] = v2;
			m_vertex[2] = v3;
			Vec2 m_vertex_temp = {};

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

		void Triangle::fillBottomFlatTriangle(HDC hdc, Vec2 v1, Vec2 v2, Vec2 v3) {
			float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
			float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

			float curx1 = v1.x;
			float curx2 = v1.x;

			for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++) {

				MoveToEx(hdc, curx1, scanlineY, NULL);
				LineTo(hdc, curx2, scanlineY);

				curx1 += invslope1;
				curx2 += invslope2;
			}
		}
		void Triangle::fillTopFlatTriangle(HDC hdc,  Vec2 v1, Vec2 v2, Vec2 v3) {
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