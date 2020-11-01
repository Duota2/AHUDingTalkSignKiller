// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
void ClickPos(int x,int y) {
    SetCursorPos(x, y);//对齐AHU位置
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(100);
}
/*
void SwapPos(int x, int y, int distance) {
    SetCursorPos(x, y);//对齐表格下滑块位置
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
    HWND hq = FindWindow( lpc,NULL);

    for (int i = 0; i < defaultCount; i++) {

        RECT rect;
        GetWindowRect(hq, &rect);
        int w = rect.right - rect.left, h = rect.bottom - rect.top;
        cout << "宽:" << w << " " << "高:" << h << endl;
        MoveWindow(hq, 0, 0, w, h, false);
        Sleep(100);
        hqarr[i] = {hq, rect};
        hq = ::FindWindowEx(NULL, hq, lpc, NULL);
    }


    for (int i = 0; i < defaultCount; i++) {
       
        SetWindowPos(hqarr[i].windowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//对齐DingTalk窗口
        Sleep(100);
        SetWindowPos(hqarr[i].windowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//确保置顶
        Sleep(100);
        SetWindowPos(hqarr[i].windowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//确保置顶
        Sleep(1000);

        RECT winPos = hqarr[i].windowPos;
        Sleep(100);
        ClickPos(winPos.left + 154, winPos.top + 170);//重置AHU位置
        Sleep(100);
        ClickPos(winPos.left + 154, winPos.top + 231);//重置AHU表格
        Sleep(100);
        ClickPos(winPos.left + 154, winPos.top + 170);//对齐AHU位置
        Sleep(1000);
        ClickPos(winPos.left + 560, winPos.top + 573);//对齐开始填写位置

        Sleep(1000);
      
        LPCSTR tipN = TEXT("CUICef2ProjectWnd");//寻找新创建的签到面板
        HWND newhq = FindWindow(tipN, NULL);
        RECT tipPos;
       
        GetWindowRect(newhq, &tipPos);
        MoveWindow(newhq, 0, 0, tipPos.right - tipPos.left, tipPos.bottom - tipPos.top, false);
        SetWindowPos(newhq, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//对齐签到窗口
        GetWindowRect(newhq, &tipPos);
        Sleep(loadingTime);
        HANDLE hThread;
        DWORD dwThreadId;

        hThread = CreateThread(NULL	// 默认安全属性
            , NULL		// 默认堆栈大小
            , TimeCounter // 线程入口地址
            , NULL	//传递给线程函数的参数
            , 0		// 指定线程立即运行
            , &dwThreadId	//线程ID号
        );

       while(1) {
           if (isCounted == 1) {
               break;
           }
           mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -500, 0);
           Sleep(10);
        }

        CloseHandle(hThread);	//关闭线程句柄，内核引用计数减一

        
        Sleep(100);
       ClickPos(winPos.left + 229, winPos.top + 604);//对齐确认提交位置
        Sleep(1000);
        ::SendMessage(newhq, WM_CLOSE, 0, 0);//关闭签到面板
    }
}


    
    

  


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
