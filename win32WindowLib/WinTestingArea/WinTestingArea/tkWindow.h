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
					rect.left + rect.right - rect.left,
					rect.top + rect.bottom - rect.top,
					hwnd,
					NULL,
					GetModuleHandle(NULL),
					NULL
				); _hwnd = hwndObject;
			}
			HWND hwnd() { return _hwnd; }
		private:
			HWND _hwnd;
		};

		struct WinImage {
			WinImage() {
				bmpSource = NULL;
				hdcSource = NULL;
			}
			void Load(tk::String file) {
				bmpSource = (HBITMAP)LoadImage(NULL, file.data, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				hdcSource = CreateCompatibleDC(GetDC(0));
			}
			void Select() { SelectObject(hdcSource, bmpSource); }
			void Draw(HDC hdc, RECT rect){
				BitBlt(
					hdc,
					rect.left, rect.top,
					rect.right,
					rect.bottom,
					hdcSource, 0, 0, SRCCOPY
				);
			}
		private:
			HBITMAP bmpSource;
			HDC hdcSource;
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

			// ---- KEYBOARD EVENTS ----
			virtual void OnKeyDown(UINT key) {}
			virtual void OnKeyUp(UINT key) {}

			// ---- WINDOW EVENTS ----
			virtual void OnWindowMinamize() {}
			virtual void OnWindowMaximize() {}
			virtual void OnScreenSave(){}
			virtual void OnWindowMove(){}
			virtual void OnWindowStopMoving(){}

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