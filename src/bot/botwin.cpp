// botwin.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "bot.h"
#include "botwin.h"
#include "afxdialogex.h"

#include <arris/net/net.hpp>
#include <arris/net/websocket.hpp>

using namespace arris::net;

// botwin 对话框

IMPLEMENT_DYNAMIC(botwin, CDialogEx)


inet_ptr ptr;
botwin::botwin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

botwin::~botwin()
{
}

void botwin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(botwin, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

// botwin 消息处理程序
void botwin::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	ptr->stop();
	/*----------释放掉注入的dll-------------*/
	HINSTANCE hInstance = AfxGetInstanceHandle();
	__OutputDebugString(TEXT("instance:%x\n"), hInstance);
	FreeLibraryAndExitThread(hInstance, 0);
	/*----------释放掉注入的dll-------------*/
	CDialogEx::OnClose();
}

DWORD WINAPI WebsocketServerThreadProc(_In_ LPVOID lpParameter) {
	netcreate<inet, wsserver> server;
	ptr = server.create();
	ptr->start();
	return 0;
}
int botwin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD dwThreadId;
	::CreateThread(0, 0, WebsocketServerThreadProc, 0, 0, &dwThreadId);

	return 0;
}


void botwin::OnNcPaint()
{
	return;//注释掉return,可隐藏窗口
	static int i = 2;
	if (i > 0)
	{

		i--;
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialog::OnNcPaint();
	}
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
}
