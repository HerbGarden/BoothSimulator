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

// CBoothInfo ���Դϴ�.

class CBoothInfo : public CView
{
	DECLARE_DYNCREATE(CBoothInfo)

protected:
	CBoothInfo();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void OnDraw(CDC* pDC) ;     // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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


