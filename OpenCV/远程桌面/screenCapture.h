/*****************************************
 * Screen Capture for OpenCV (>= 2.1)    *
 * by JR                                 *
 *****************************************/

/**********************************************************************
 ** Quick usage:                                                      *
 *                                                                    *
 * WindowCapture cap(hWnd);                                           *
 * Mat dst;                                                           *
 * cap.captureFrame(dst);                                             *
 *                                                                    *
 * Use getHwndsByProcessName() to get a list of the window handles    *
 * (hWnds) for a given process.                                       *
 *                                                                    *
 * To capture a DirectX/OpenGL-rendered window, set the 'screenshot'  *
 * parameter on the constructor to true. This will take a screenshot  *
 * of the composed desktop and crop out the desired window.           *
 *                                                                    *
 **********************************************************************/

#pragma once

#include <vector>
#include <windows.h>
#include <opencv/cv.h>

struct CaptureState
{
    HWND window;
    int width, height;
    RECT wr, cr;

    bool screenshot;
    HDC windowDc;
    HDC memDc;
    HBITMAP hbmp;
    BITMAPINFOHEADER bi;
};

class WindowCapture
{
private:
    const bool screenshot;
    CaptureState* state;

    void initialize();

public:
    const HWND window;

    WindowCapture(HWND window, bool screenshot = false);
    ~WindowCapture();

    int width();
    int height();
    void captureFrame(cv::Mat& dst);
};

void getHwndsByProcessId(DWORD processId, std::vector<HWND>& list, bool visibleOnly = true);
void getHwndsByProcessName(const wchar_t* processName, std::vector<HWND>& list, bool visibleOnly = true);
void revealWindow(HWND window);

CaptureState* beginCaptureWindow(HWND window, bool screenshot = false);
void endCaptureWindow(CaptureState*& cs);
void captureFrame(const CaptureState* cs, cv::Mat& dst);

void captureWindow(HWND window, cv::Mat& dst, bool screenshot = false);
