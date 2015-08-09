#include "screenCapture.h"
#include <psapi.h>

using namespace std;
using namespace cv;

struct GetHwndsState
{
    DWORD processId;
    vector<HWND>& list;
    bool visibleOnly;
};

BOOL CALLBACK enumWindows(HWND hWnd, LPARAM lParam)
{
    GetHwndsState* state = (GetHwndsState*)lParam;

    if (state->visibleOnly && !(GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE))
        return true;

    DWORD processId;
    GetWindowThreadProcessId(hWnd, &processId);

    if (processId == state->processId)
        state->list.push_back(hWnd);

    return true;
}

void getHwndsByProcessId(DWORD processId, vector<HWND>& list, bool visibleOnly)
{
    GetHwndsState state = { processId, list, visibleOnly };
    EnumWindows(enumWindows, (LPARAM)&state);
}

void getHwndsByProcessName(const wchar_t* processName, vector<HWND>& list, bool visibleOnly)
{
    DWORD* pids = new DWORD[1024];
    DWORD bytesReturned;

    EnumProcesses(pids, 1024 * sizeof(DWORD), &bytesReturned);

    int processes = bytesReturned / sizeof(DWORD);
    wchar_t* nameBuffer = new wchar_t[1024];

    for (int i = 0; i < processes; i++)
    {
        HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION, false, pids[i]);
        if (!process)
            continue;

        if (GetProcessImageFileNameW(process, nameBuffer, 1024)
            && wcsstr(nameBuffer, processName) - nameBuffer == wcslen(nameBuffer) - wcslen(processName))
            getHwndsByProcessId(GetProcessId(process), list, visibleOnly);

        CloseHandle(process);
    }

    delete[] pids, nameBuffer;
}

void moveRect(RECT& rect, int x, int y)
{
    rect.left += x, rect.right += x;
    rect.top += y, rect.bottom += y;
}

bool overlapRect(const RECT& a, const RECT& b)
{
    return (a.left >= b.left && a.left < b.right || a.right > b.left && a.right <= b.right)
        && (a.top >= b.top && a.top < b.bottom || a.bottom > b.top && a.bottom <= b.bottom);
}

void revealWindow(HWND window)
{
    if (!IsWindow(window))
        throw exception("Window does not exist.");

    if (IsIconic(window))
        SendMessage(window, WM_SYSCOMMAND, SC_RESTORE, 0);

    RECT cr;
    GetClientRect(window, &cr);

    POINT clientOffset = { 0, 0 };
    if (!ClientToScreen(window, &clientOffset))
        throw exception("Could not get client area offset.");

    moveRect(cr, clientOffset.x, clientOffset.y);

    // Find the HWND of the window after which to insert the current window
    // in z-order. This is the window in front of the topmost window occluding
    // the current window (if any).
    bool targetNext = false;
    HWND target = 0;
    HWND next = window;
    while (next = GetWindow(next, GW_HWNDPREV))
    {
        RECT wr;
        GetWindowRect(next, &wr);
        
        if (overlapRect(wr, cr))
            targetNext = true;
        else if (targetNext)
            target = next, targetNext = false;
    }

    if (targetNext)
        SetForegroundWindow(window);
    else if (target)
        SetWindowPos(window, target, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
}

CaptureState* beginCaptureWindow(HWND window, bool screenshot)
{
    if (!IsWindow(window))
        throw exception("Window does not exist.");

    CaptureState* cs = new CaptureState();

    cs->window = window;
    cs->screenshot = screenshot;

    try
    {
        cs->windowDc = GetWindowDC(screenshot ? 0 : window);
        cs->memDc = CreateCompatibleDC(cs->windowDc);

        if (!cs->windowDc || !cs->memDc)
            throw exception("Could not get the required device contexts.");

        GetWindowRect(window, &cs->wr);
        GetClientRect(window, &cs->cr);

        POINT clientOffset = { 0, 0 };
        if (!ClientToScreen(window, &clientOffset))
            throw exception("Could not get client area offset.");

        moveRect(cs->cr, clientOffset.x, clientOffset.y);

        cs->width = cs->cr.right - cs->cr.left;
        cs->height = cs->cr.bottom - cs->cr.top;
        
        if (cs->width == 0 || cs->height == 0)
            throw exception("Client area width or height is zero.");

        cs->hbmp = CreateCompatibleBitmap(cs->windowDc, cs->width, cs->height);

        if (!cs->hbmp)
            throw exception("Could not create bitmap.");

        SelectObject(cs->memDc, cs->hbmp);
        
        BITMAPINFOHEADER bi =
        {
            sizeof(BITMAPINFOHEADER),   // biSize
            cs->width,                  // biWidth
            -cs->height,                // biHeight
            1,                          // biPlanes
            32,                         // biBitCount
            BI_RGB,                     // biCompression
            0,                          // biSizeImage
            0,                          // biXPelsPerMeter
            0,                          // biYPelsPerMeter
            0,                          // biClrUser
            0                           // biClrImportant
        };
        cs->bi = bi;

        return cs;
    }
    catch (exception e)
    {
        endCaptureWindow(cs);
        throw e;
    }
}

void endCaptureWindow(CaptureState*& cs)
{
    if (!cs)
        return;

    DeleteObject(cs->hbmp);
    DeleteObject(cs->memDc);
    ReleaseDC(cs->screenshot ? 0 : cs->window, cs->windowDc);
    
    delete cs;
    cs = 0;
}

void captureFrame(const CaptureState* cs, Mat& dst)
{
    if (!cs)
        throw exception("Capture state is null.");

    int offsetX = cs->cr.left;
    int offsetY = cs->cr.top;
    if (!cs->screenshot)
        offsetX -= cs->wr.left, offsetY -= cs->wr.top;

    if (!BitBlt(cs->memDc, 0, 0, cs->width, cs->height, cs->windowDc, offsetX, offsetY, SRCCOPY))
        throw exception("Copying between device contexts failed.");

    dst.create(cs->height, cs->width, CV_8UC4);

    if (!dst.data)
        throw exception("Could not allocate destination matrix.");
        
    int success = GetDIBits(cs->memDc, cs->hbmp, 0, (UINT)cs->height, dst.data, (BITMAPINFO*)&cs->bi, DIB_RGB_COLORS);

    if (!success || success == ERROR_INVALID_PARAMETER)
        throw exception("Could not copy bitmap to matrix.");
}

void captureWindow(HWND window, Mat& dst, bool screenshot)
{
    CaptureState* cs = beginCaptureWindow(window, screenshot);
    try
    {
        captureFrame(cs, dst);
        endCaptureWindow(cs);
    }
    catch (exception e)
    {
        endCaptureWindow(cs);
        throw e;
    }
}

/* class WindowCapture */

WindowCapture::WindowCapture(HWND window, bool screenshot)
    : window(window), screenshot(screenshot), state(0)
{ }

WindowCapture::~WindowCapture()
{
    if (state)
        endCaptureWindow(state);
}

void WindowCapture::initialize()
{
    if (state)
        return;

    if (screenshot)
        revealWindow(window);

    state = beginCaptureWindow(window, screenshot);
}

int WindowCapture::width()
{
    initialize();
    return state->width;
}

int WindowCapture::height()
{
    initialize();
    return state->height;
}

void WindowCapture::captureFrame(Mat& dst)
{
    initialize();
    ::captureFrame(state, dst);
}
