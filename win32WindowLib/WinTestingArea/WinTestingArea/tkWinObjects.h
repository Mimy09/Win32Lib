#pragma once
#include <tkString.h>
#include <Windows.h>

namespace tk {
	namespace win {
		

		struct WinObject {
			WinObject() { _hwnd = nullptr; }
			/* ---- WinObject ----
			Constructor for the WinObject
			#param hwnd - The window handler
			#param classType - The type of window that will be created
			e.g. "BUTTON", "LISTBOX"
			#param text - The text that will be displayed in the window
			#param rect - The local position that the window will be created at */
			WinObject(HWND hwnd, tk::String classType, tk::String text, RECT rect) {
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
			/* ---- CreateWnd ----
			Creates a WinObject
			#param hwnd - The window handler
			#param classType - The type of window that will be created
			e.g. "BUTTON", "LISTBOX"
			#param text - The text that will be displayed in the window
			#param rect - The local position that the window will be created at */
			void CreateWnd(HWND hwnd, tk::String classType, tk::String text, RECT rect) {
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
			/* ---- SetTextSize ----
			Sets the size of text that will be displayed inside the window
			#param Size - The size of text */
			void SetTextSize(int Size) {
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
			/* ---- SetPosition ----
			Sets the position of the window
			#param rect - The rect that will be used to set the position*/
			void SetPosition(RECT rect) {
				MoveWindow(
					_hwnd,
					rect.left, rect.top,
					rect.right, rect.bottom,
					true
				);
			}
			/* ---- hwnd ----
			Return the window handle of this window
			#return HWND - returns the window handle*/
			HWND hwnd() { return _hwnd; }
		private:
			// Stores the window handle of the created window
			HWND _hwnd;
		};

		struct WinImage {
			/* ---- WinImage ----
			Creates an image to be drawn on screen */
			WinImage() {
				bmpSource = NULL;
				hdcSource = NULL;
			}
			/* ---- Load ----
			Loads a selected file in to draw
			#param file - The path to the image*/
			void Load(tk::String file) {
				bmpSource = (HBITMAP)LoadImage(NULL, file.data, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				hdcSource = CreateCompatibleDC(GetDC(0));
			}
			/* ---- Secect ----
			Selects the image so it can be drawn
			@NOTE - This needs to be called befor drawing*/
			void Select() { SelectObject(hdcSource, bmpSource); }
			/* ---- Draw ----
			Draws the image to screen
			#param hdc - The handle to the display
			#param rect - The rect that the image is drawn to
			@NOTE - Select() needs to be called befor drawing*/
			void Draw(HDC hdc, RECT rect) {
				BitBlt(
					hdc,
					rect.left, rect.top,
					rect.right, rect.bottom,
					hdcSource, 0, 0, SRCCOPY
				);
			}
		private:
			// Stores the bitmap of the image
			HBITMAP bmpSource;
			// Stores the handle to the display
			HDC hdcSource;
		};

		struct WinText {
			WinText(){
				font = NULL;
				hFontOld = NULL;
			}
			/* ---- WinText ----
			Default constructor for WinText
			#param hdc -The handle to the display
			#param Text - The text that will be displayed
			#param Position - The position that the text will be displayed at*/
			WinText(HDC hdc, tk::String Text, RECT Position) {
				pos = {
					Position.left, Position.top,
					Position.left + Position.right,
					Position.top + Position.bottom
				};
				SelectObject(hdc, font);
				DrawText(hdc, Text.data, strlen(Text.data), &pos, DT_CENTER);
				SelectObject(hdc, hFontOld);
			}
			void Draw(HDC hdc, tk::String Text, RECT Position) {
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
			void SetFont(int size) {
				font = CreateFont(
					size, 0, 0, 0,
					FW_DONTCARE,
					FALSE, FALSE, FALSE,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_SWISS,
					"Arial"
				); 
			}
			HFONT font;
		private:
			// Stores the position of the text
			RECT pos;
			HFONT hFontOld;
		};
	}
}