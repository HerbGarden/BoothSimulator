#pragma once
#include "resource.h"
#include "stdafx.h"

// CBoothInit ��ȭ �����Դϴ�.

class CBoothInit : public CDialogEx
{
	DECLARE_DYNAMIC(CBoothInit)

public:
	CBoothInit(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBoothInit();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_Setting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString Name;
	int possibleCnt;
	int useTime;
	afx_msg void OnBnClickedOk();
};
