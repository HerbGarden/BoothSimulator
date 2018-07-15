// BoothInit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Project.h"
#include "BoothInit.h"
#include "afxdialogex.h"


// CBoothInit 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBoothInit, CDialogEx)

CBoothInit::CBoothInit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBoothInit::IDD, pParent)
	, Name(_T(""))
	, possibleCnt(0)
	, useTime(0)
{
}

CBoothInit::~CBoothInit()
{
}

void CBoothInit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Name);
	DDV_MaxChars(pDX, Name, 20);
	DDX_Text(pDX, IDC_EDIT2, possibleCnt);
	DDX_Text(pDX, IDC_EDIT3, useTime);
}


BEGIN_MESSAGE_MAP(CBoothInit, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBoothInit::OnBnClickedOk)
END_MESSAGE_MAP()


// CBoothInit 메시지 처리기입니다.


void CBoothInit::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CDialogEx::OnOK();
}
