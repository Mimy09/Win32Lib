/*************************************************
					  TOOL KIT
			Mitchell Jenkins 12-May-17
**************************************************/
#pragma once

/** Includes */
#include <Windows.h>
#include <tkException.h>
#include <tkObjectPool.h>
#include "tkTimer.h"

/** Definitions */
#define TK_WinMain() WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cCmdShow)
#define TK_WinProc() CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define TK_BtnWinProc() CALLBACK WinProcBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define TK_DEFWINPROC DefWindowProc(hwnd, msg, wParam, lParam)

#define TK_UPDATE_RECT(_hwnd_,_rect_) InvalidateRect(_hwnd_, _rect_, false);UpdateWindow(_hwnd_);

#define TK_MSG_EXIT -1
#define TK_MSG_UPDATE 0
#define TK_MSG_DISPATCH 1

#define TK_BRUSH_BLACK *brushPool.ReturnObject(0)
#define TK_BRUSH_WHITE *brushPool.ReturnObject(1)
#define TK_BRUSH_RED *brushPool.ReturnObject(2)
#define TK_BRUSH_GREEN *brushPool.ReturnObject(3)
#define TK_BRUSH_BLUE *brushPool.ReturnObject(4)

namespace tk {
	namespace win {

		struct WinObject {
			WinObject() {_hwnd = nullptr; }
			/* ---- WinObject ----
			Constructor for the WinObject
			#param hwnd - The window handler
			#param classType - The type of window that will be created
				e.g. "BUTTON", "LISTBOX"
			#param text - The text that will be displayed in the window
			#param rect - The local position that the window will be created at */
			WinObject(HWND hwnd, tk::String classType,  tk::String text, RECT rect) {
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
			void Draw(HDC hdc, RECT rect){
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
				DrawText(hdc, Text.data, strlen(Text.data), &pos, DT_LEFT);
			}
		private:
			// Stores the position of the text
			RECT pos;
		};

		class Window {
		public:

			//##################################//
			// PUBLIC VARIABLES
			//##################################//
			//Stores the Bitmap of the whole screen to alow for double buffering 
			HBITMAP hBitmat;
			//The second HDC to swap to whilse double buffering 
			HDC memDC;
			//Screen Width
			int screenWidth = 0;
			//Screen Height
			int screenHeight = 0;



			//##################################//
			// CONSTRUCTOR
			//##################################//
			// Defalt constructor
			Window(){}
			// Defalt virtual deconstructor
			virtual ~Window() = 0 {}


			//##################################//
			// PUBLIC FUNCTIONS
			//##################################/

			/* ---- Create ----
			* #param className - Sets the class name of the WINCLASS 
			* #param winTitle - Sets the title of the main HWND window
			* #param winPos - Sets the position of the main HWND window */
			virtual void Create(tk::String className, tk::String winTitle, RECT winPos);
			
			/* ---- Show ---- 
			Sets the main HWND window to visable */
			virtual void Show();
			
			/* ---- Hide ----
			Set the main HWND window to hidden */
			virtual void Hide();

			/* ---- Run ---- 
			Runs the main message loop
			#return int (-1) - If WM_QUIT was posted
			#return int (0) - If all messages have been dispatched
			#return int (1) - If messages are being dispatched*/
			virtual int Run();

			/* ---- Update ----
			virtual Update loop
			#param deltaTime - The delta time of the app*/
			virtual void Update(double deltaTime);

			/* ---- ScreenRectWidth ----
			Gets the Screen width
			#return int - Returns the screen width*/
			virtual inline int ScreenRectWidth() { GetClientRect(_hwnd, &_rc); return _rc.right - _rc.left; }

			/* ---- ScreenRectHeight ----
			Gets the Screen height
			#return int - Returns the screen height*/
			virtual inline int ScreenRectHeight() { GetClientRect(_hwnd, &_rc); return _rc.bottom - _rc.top; }

			// Sets the WinProc as a friend of this class
			friend LRESULT TK_WinProc();

			/* ---- hwnd ----
			Gets the hwnd
			#return HWND - Returns the hwnd*/
			inline HWND hwnd() { return _hwnd; }

			/* ---- UpdateTime ----
			Updates the prevTime of the deltaTime */
			inline void UpdateTime() { prevTime = _timer.elapsed(); }


		protected:
			//##################################//
			// POLYMOPHIC FUNCTIONS
			//##################################//
			
			/* ---- OnCreate ----
			Called when the WM_CREATE message is dispatched
			#param hwnd - The window handle of the current window
			#return bool (true) - If no error in window
			#return bool (false) - If error in window*/
			virtual bool OnCreate(HWND hwnd) { return true; } // return false if error / close window


			/* ---- OnDestroy ----
			Called when the WM_DESTROY message is dispatched
			#defalt body - PostQuitMessage(0); */
			virtual void OnDestroy() { PostQuitMessage(0); }

			/* ---- OnClose ----
			Called when the WM_CLOSE message is dispatched*/
			virtual void OnClose() {}


			/* ---- OnPaint ----
			Called when the WM_PAINT message is dispatched
			#param hdc - The device context*/
			virtual void OnPaint(HDC hdc) {}

			
			// ---- MOUSE EVENTS ----
			virtual void OnMouseDown(int x, int y, UINT param) {}
			virtual void OnMouseUp(int x, int y, UINT param) {}
			virtual void OnMouseMove(int x, int y, UINT param) {}
			virtual void OnMouseDClick(int x, int y, UINT param) {}
			
			// ---- BUTTON EVENTS ----
			virtual void OnBtnClicked(HWND wndHandle) {}
			virtual void OnBtnDBClicked(HWND wndHandle) {}
			virtual void OnBtnPushed(HWND wndHandle) {}
			virtual void OnBtnUnpushed(HWND wndHandle) {}

			// ---- KEYBOARD EVENTS ----
			virtual void OnKeyDown(UINT key) {}
			virtual void OnKeyUp(UINT key) {}

			// ---- WINDOW EVENTS ----
			virtual void OnWindowMinamize() {}
			virtual void OnWindowMaximize() {}
			virtual void OnScreenSave(){}
			virtual void OnWindowMove(){}
			virtual void OnWindowStopMoving(){}
			virtual void OnWindowResize(){}

			tk::ObjectPool<HBRUSH> brushPool;

		private:
			MSG _msg;
			RECT _rc;
			HWND _hwnd;
			Timer _timer;
			WNDCLASSEX _wc;

			double prevTime = 0;
		};
	}
}