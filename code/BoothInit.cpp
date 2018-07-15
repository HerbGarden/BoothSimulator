// BoothInit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Project.h"
#include "BoothInit.h"
#include "afxdialogex.h"


// CBoothInit ��ȭ �����Դϴ�.

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


// CBoothInit �޽��� ó�����Դϴ�.


void CBoothInit::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CDialogEx::OnOK();
}
