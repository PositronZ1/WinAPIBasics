#include <stdio.h>
#include <windows.h>

const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_LBUTTONDOWN:
        {
            MessageBox(hwnd, "Left button pressed.", "Note", MB_OK);
            char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);
            
            GetModuleFileName(hInstance, szFileName, MAX_PATH);
            MessageBox(hwnd, szFileName, "PROGRAM NAME", MB_OK | MB_ICONEXCLAMATION);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            MessageBox(hwnd, "Right button pressed.", "Note", MB_OK);
            HINSTANCE hInstance = GetModuleHandle(NULL);
            HWND hwnd = GetActiveWindow();
            
            SetWindowText(hwnd, "Test Window 2");
            
            break;
        }
        case WM_MBUTTONDOWN:
            MessageBox(hwnd, "Middle button pressed.", "Note", MB_OK);
            break;
        case WM_CLOSE:
            MessageBox(hwnd, "YOU ARE DESTROYING ME!!!", "NOOOOOO!", MB_OK);
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;
    DWORD dw = GetLastError();
    
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_ERROR);
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_ERROR);
    
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "failed to register window class", "Fatal error", MB_OK);
        return -1;
    }
    
    hwnd = CreateWindow(g_szClassName, "Test Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, hInstance, NULL);
    
    if (!hwnd)
    {
        MessageBox(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return -1;
    }
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
