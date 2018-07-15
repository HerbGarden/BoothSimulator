#include "stdafx.h"
#include "ProjectDoc.h"
#include "BoothInit.h"
#include "resource.h"
#include "ProjectView.h"

#pragma once

#define INFODEFAULT 1
#define INFO 2
#define INFOSETTING 3
#define INFODELETE 4
#define INFOIMAGE 5
#define INFONOTTING 0

// CBoothInfo 뷰입니다.

class CBoothInfo : public CView
{
	DECLARE_DYNCREATE(CBoothInfo)

protected:
	CBoothInfo();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CBoothInfo();
	void OnInitialUpdate();
public:
	CString Name;
	CString Time;
	CString Pre;
	CString InPeo;
	int m_ClickState;
	int m_selectState;
	CRect rSetting, rDelete, rImage;
	CBoothInit BI;
	int index;
	void mainFrmEvent();
	void SetStr();

	void GetBmp(CBitmap*);
	virtual void OnDraw(CDC* pDC) ;     // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


