// ConsoleApplication2.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string.h>

using namespace std;
const int defaultCount = 1;
const int loadingTime = 5000;
const int defaultAHUX = 159;
const int defaultAHUY = 165;
const int PosMode = 0;
bool isCounted = 0;
struct DingWin {
    HWND windowHandle;
    RECT windowPos;
}DingWindow;
void ClickPos(int x, int y) {
    SetCursorPos(x, y);//����AHUλ��
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(100);
}
/*
void SwapPos(int x, int y, int distance) {
    SetCursorPos(x, y);//�������»���λ��
    Sleep(500);
  //  mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(10);
    //mouse_event(MOUSEEVENTF_MOVE, 0, distance, 0, 0);

    Sleep(10);
  //  mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(10);
}
*/

DWORD WINAPI TimeCounter(LPVOID lpParam)
{
    Sleep(500);
    isCounted = 1;
    return 0;
}
void ScrollToBottom() {
    HANDLE hThread;
    DWORD dwThreadId;
    hThread = CreateThread(NULL	// Ĭ�ϰ�ȫ����
        , NULL		// Ĭ�϶�ջ��С
        , TimeCounter // �߳���ڵ�ַ
        , NULL	//���ݸ��̺߳����Ĳ���
        , 0		// ָ���߳���������
        , &dwThreadId	//�߳�ID��
    );

    while (1) {
        if (isCounted == 1) {
            isCounted = 0;
            break;
        }
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -500, 0);
        Sleep(10);
    }

    CloseHandle(hThread);	//�ر��߳̾�����ں����ü�����һ
}
int main(int argc, char* argv[])
{
    system("c:\\Program Files (x86)\\DingDing\\main\\current\\DingTalk.exe");
    //ShellExecuteA(NULL, "open", "c:\\Program Files (x86)\\DingDing\\main\\current\\DingTalk.exe", NULL, NULL, SW_SHOW);
    Sleep(1000);
    if (PosMode == 1) {
        while (1) {
            POINT p;
            GetCursorPos(&p);
            cout << "X:" << p.x << "Y:" << p.y << endl;
            Sleep(10);
        }
    }
    DingWin hqarr[defaultCount];
    LPCSTR lpc = TEXT("StandardFrame_DingTalk");
    HWND hq = FindWindow(lpc, NULL);

    for (int i = 0; i < defaultCount; i++) {

        RECT rect;
        GetWindowRect(hq, &rect);
        int w = rect.right - rect.left, h = rect.bottom - rect.top;
        cout << "��:" << w << " " << "��:" << h << endl;
        MoveWindow(hq, 0, 0, w, h, false);
        Sleep(100);
        hqarr[i] = { hq, rect };
        hq = ::FindWindowEx(NULL, hq, lpc, NULL);
        /*LPSTR title = {0};
        GetWindowTextA(hq, title, MAX_PATH);
        if (title != "����") {

        }*/
    }


    for (int i = 0; i < defaultCount; i++) {
        if (IsIconic(hqarr[i].windowHandle)) {
            ShowWindow(hqarr[i].windowHandle, SW_SHOWNORMAL);
        }
        Sleep(100);
        GetWindowRect(hq, &hqarr[i].windowPos);
        Sleep(100);
        SetWindowPos(hqarr[i].windowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//����DingTalk����
        Sleep(100);
        SetWindowPos(hqarr[i].windowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//ȷ���ö�
        Sleep(100);
        SetWindowPos(hqarr[i].windowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//ȷ���ö�
        Sleep(1000);

        // RECT winPos = hqarr[i].windowPos;
         /*Sleep(100);
         ClickPos( 154,  170);//����AHUλ��
         Sleep(100);
         ClickPos( 154,  231);//����AHU���
         Sleep(100);
         ClickPos( 154, 170);//����AHUλ��*/
        ScrollToBottom();
        Sleep(1000);
        ClickPos(560, 573);//���뿪ʼ��дλ��

        Sleep(1000);

        LPCSTR tipN = TEXT("CUICef2ProjectWnd");//Ѱ���´�����ǩ�����
        HWND newhq = FindWindow(tipN, NULL);
        RECT tipPos;

        GetWindowRect(newhq, &tipPos);
        MoveWindow(newhq, 0, 0, tipPos.right - tipPos.left, tipPos.bottom - tipPos.top, false);
        SetWindowPos(newhq, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//����ǩ������
        GetWindowRect(newhq, &tipPos);
        SetFocus(newhq);
        Sleep(loadingTime);
        ScrollToBottom();
        Sleep(1000);
        ClickPos(229, 604);//����ȷ���ύλ��
        Sleep(1000);
        ::SendMessage(newhq, WM_CLOSE, 0, 0);//�ر�ǩ�����
    }
}
