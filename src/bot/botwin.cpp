// botwin.cpp: 实现文件
//

#include "pch.h"
#include "bot.h"
#include "botwin.h"
#include "afxdialogex.h"


// botwin 对话框

IMPLEMENT_DYNAMIC(botwin, CDialogEx)

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
END_MESSAGE_MAP()


// botwin 消息处理程序


void botwin::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


int botwin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}
