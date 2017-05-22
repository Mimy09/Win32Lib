#include "tkWindow.h"

int main();

namespace tk {
	namespace win {

		LRESULT TK_WinProc() {
			tk::win::Window* win = (tk::win::Window *) GetWindowLong(hwnd, 0);

			switch (msg) {
			case WM_NCCREATE:
			{
				CREATESTRUCT * cs = (CREATESTRUCT *)lParam;
				SetWindowLong(hwnd, 0, (LONG)cs->lpCreateParams);
				break;
			}
			case WM_CREATE:
			{
				win->screenWidth = GetSystemMetrics(SM_CXSCREEN);
				win->screenHeight = GetSystemMetrics(SM_CYSCREEN);

				HDC hdc = GetDC(hwnd);
				win->memDC = CreateCompatibleDC(hdc);
				win->hBitmat = CreateCompatibleBitmap(hdc, win->screenWidth, win->screenHeight);
				SelectObject(win->memDC, win->hBitmat);
				ReleaseDC(hwnd, hdc);

				if (win->OnCreate(hwnd)) break; return -1;
			}
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				win->OnPaint(win->memDC);
				BitBlt(hdc, 0, 0, win->screenWidth, win->screenHeight, win->memDC, 0, 0, SRCCOPY);
				EndPaint(hwnd, &ps);
				break;
			}
			case WM_ERASEBKGND: return 1;
			case WM_DESTROY: win->OnDestroy(); break;
			case WM_CLOSE: win->OnClose(); break;
			case WM_SYSCOMMAND:
				if ((wParam & 0xFFF0) == SC_MINIMIZE) { win->OnWindowMinamize(); }
				if ((wParam & 0xFFF0) == SC_MAXIMIZE) { win->UpdateTime(); win->OnWindowMaximize(); }
				if ((wParam & 0xFFF0) == SC_SCREENSAVE) { win->UpdateTime(); win->OnScreenSave(); }
				break;
			case WM_COMMAND:
				switch (LOWORD(wParam)) {
				case BN_CLICKED: win->OnBtnClicked((HWND)lParam); break;
				case BN_DBLCLK: win->OnBtnDBClicked((HWND)lParam); break;
				case BN_PUSHED: win->OnBtnPushed((HWND)lParam); break;
				case BN_UNPUSHED: win->OnBtnUnpushed((HWND)lParam); break;
				}
				break;
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP: win->OnMouseUp(LOWORD(lParam), HIWORD(lParam), wParam); break;
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN: win->OnMouseDown(LOWORD(lParam), HIWORD(lParam), wParam); break;
			case WM_LBUTTONDBLCLK: win->OnMouseDClick(LOWORD(lParam), HIWORD(lParam), wParam); break;
			case WM_MOUSEMOVE: win->OnMouseMove(LOWORD(lParam), HIWORD(lParam), wParam); break;
			case WM_KEYDOWN: win->OnKeyDown(wParam); break;
			case WM_KEYUP: win->OnKeyUp(wParam); break;
			case WM_MOVE: win->OnWindowMove(); break;
			case WM_EXITSIZEMOVE: win->UpdateTime(); win->OnWindowStopMoving(); break;
			case WM_SIZING: win->OnWindowResize(); break;
			}
			return TK_DEFWINPROC;
		}

		void Window::Create(tk::String className, tk::String winTitle, RECT winPos) {
			ZeroMemory(&_wc, sizeof(WNDCLASSEX));
			ZeroMemory(&_msg, sizeof(MSG));
			HINSTANCE hInstance = GetModuleHandle(NULL);

			this->_wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
			this->_wc.style = CS_HREDRAW | CS_VREDRAW;
			this->_wc.cbSize = sizeof(WNDCLASSEX);
			this->_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			this->_wc.hIconSm = LoadIcon(_wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
			this->_wc.hInstance = hInstance;
			this->_wc.cbClsExtra = 0;
			this->_wc.cbWndExtra = sizeof(void*);
			this->_wc.lpfnWndProc = WinProc;
			this->_wc.lpszMenuName = NULL;
			this->_wc.lpszClassName = className.data;
			this->_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			if (!RegisterClassEx(&_wc)) TK_EXCEPTION("WINDOW ERROR");

			RECT rectPos = { winPos.left, winPos.top, 0, 0 };
			AdjustWindowRectEx(&winPos, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

			this->_hwnd = CreateWindowEx(
				WS_EX_OVERLAPPEDWINDOW,
				className.data,
				winTitle.data,
				WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
				rectPos.left == 0 ? CW_USEDEFAULT : rectPos.left,
				rectPos.top == 0 ? CW_USEDEFAULT : rectPos.top,
				winPos.right - winPos.left,
				winPos.bottom - winPos.top,
				NULL,
				NULL,
				this->_wc.hInstance,
				(LPVOID) this
			);
			if (!_hwnd) TK_EXCEPTION("WINDOW ERROR");

			brushPool.AddObject(CreateSolidBrush(RGB(0, 0, 0)));
			brushPool.AddObject(CreateSolidBrush(RGB(255, 255, 255)));
			brushPool.AddObject(CreateSolidBrush(RGB(255, 0, 0)));
			brushPool.AddObject(CreateSolidBrush(RGB(0, 255, 0)));
			brushPool.AddObject(CreateSolidBrush(RGB(0, 0, 255)));

			_timer.start();
			prevTime = 0;

			version = "0.1";
			_versionFile.SetPath("../../VERSION.dat");
			_versionFile.Open(tk::IO::ReadWrite);
			_versionFile.Write(version.data);
			_versionFile.Close();

		}
		void Window::Show() {
			if (!_hwnd) TK_EXCEPTION("WINDOW HANDLE ERROR");
			ShowWindow(_hwnd, SW_SHOW);
			UpdateWindow(_hwnd);
		}
		void Window::Hide() {
			if (!_hwnd) TK_EXCEPTION("WINDOW HANDLE ERROR");
			ShowWindow(_hwnd, SW_HIDE);
			UpdateWindow(_hwnd);
		}
		int Window::Run() {
			if (_msg.message != WM_QUIT) {
				if (PeekMessage(&_msg, 0, 0, 0, PM_REMOVE)) {
					TranslateMessage(&_msg);
					DispatchMessage(&_msg);
					return 1;
				}
				else {
					double now = _timer.elapsed();
					double deltaTime = now - prevTime;
					Update(deltaTime);
					prevTime = now;
					return 0;
				}
			} else { return -1; }
		}
		void Window::Update(double deltaTime) {
			TK_UPDATE_RECT(_hwnd, NULL);
		}
	}
}

inline int TK_WinMain() {
	main();
}