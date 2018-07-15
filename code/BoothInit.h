#pragma once
#include "resource.h"
#include "stdafx.h"

// CBoothInit 대화 상자입니다.

class CBoothInit : public CDialogEx
{
	DECLARE_DYNAMIC(CBoothInit)

public:
	CBoothInit(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBoothInit();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Setting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString Name;
	int possibleCnt;
	int useTime;
	afx_msg void OnBnClickedOk();
};
